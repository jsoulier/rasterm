#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mesh.h"
#include "stb_image.h"
#include "vertex.h"

typedef struct
{
    char name[256];
    stbi_uc* data;
    int channels;
    int width;
    int height;
}
material_t;

static bool load_mtl(
    material_t* material,
    const char* root,
    const char* filename)
{
    char path[256] = {0};
    strncpy(path, root, sizeof(path));
    char* seperator;
    char* forward = strrchr(path, '/');
    char* backward = strrchr(path, '\\');
    if (forward < backward)
    {
        seperator = backward;
    }
    else
    {
        seperator = forward;
    }
    *seperator = '\0';
    strncat(seperator, filename, path - seperator);
    FILE* file = fopen(path, "r");
    if (!file)
    {
        printf("Failed to open file: %s\n", path);
        return false;
    }
    char line[256];
    memset(material->name, 0, sizeof(material->name));
    material->data = NULL;
    while (fgets(line, sizeof(line), file))
    {
        if (!strncmp(line, "newmtl ", 7))
        {
            sscanf(line, "newmtl %s", material->name);
        }
        else if (!strncmp(line, "map_Kd ", 7))
        {
            if (material->data)
            {
                printf("Image already set\n");
                return false;
            }
            sscanf(line, "newmtl %s", path);
            material->data = stbi_load(path,
                &material->width,
                &material->height,
                &material->channels, 3);
            if (material->data)
            {
                printf("Failed to load image: %s\n", path);
                return false;
            }
        }
    }
    if (!material->data)
    {
        printf("No image set: %s\n", path);
        return false;
    }
    fclose(file);
    return true;
}

bool load_obj_mesh(
    mesh_t* mesh,
    const char* path)
{
    FILE* file = fopen(path, "r");
    if (!file)
    {
        printf("Failed to open file: %s\n", path);
        return false;
    }
    char line[256];
    uint32_t num_materials = 0;
    uint32_t num_positions = 0;
    uint32_t num_colours = 0;
    uint32_t num_normals = 0;
    uint32_t num_faces = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (!strncmp(line, "mtllib ", 7))
        {
            num_materials++;
        }
        else if (!strncmp(line, "v ", 2))
        {
            num_positions++;
        }
        else if (!strncmp(line, "vt ", 3))
        {
            num_colours++;
        }
        else if (!strncmp(line, "vn ", 3))
        {
            num_normals++;
        }
        else if (!strncmp(line, "f ", 2))
        {
            num_faces++;
        }
    }
    if (!num_positions || !num_faces)
    {
        printf("Failed to read mesh: %s\n", path);
        return false;
    }
    material_t* materials = malloc(sizeof(material_t) * num_materials);
    float* positions = malloc(sizeof(float) * num_positions * 3);
    float* colours = malloc(sizeof(float) * num_colours * 3);
    float* normals = malloc(sizeof(float) * num_normals * 3);
    uint32_t* faces = malloc(sizeof(uint32_t) * num_faces * 9);
    if (!materials || !positions || !colours || !normals || !faces)
    {
        printf("Failed to allocate buffers\n");
        return false;
    }
    material_t* material = NULL;
    num_materials = 0;
    num_positions = 0;
    num_colours = 0;
    num_normals = 0;
    num_faces = 0;
    rewind(file);
    while (fgets(line, sizeof(line), file))
    {
        if (!strncmp(line, "mtllib ", 7))
        {
            char name[256] = {0};
            sscanf(line, "mtllib %s", name);
            if (!load_mtl(&materials[num_materials], path, name))
            {
                printf("Failed to load material: %s\n", name);
                return false;
            }
        }
        else if (!strncmp(line, "usemtl ", 7))
        {
            material = NULL;
            char name[256] = {0};
            sscanf(line, "usemtl %s", name);
            for (uint32_t i = 0; i < num_materials; i++)
            {
                if (!strncmp(materials[i].name, name, sizeof(name)))
                {
                    material = &materials[i];
                    break;
                }
            }
            if (!material)
            {
                printf("No material for name: %s\n", name);
                return false;
            }
        }
        else if (!strncmp(line, "v ", 2))
        {
            sscanf(line, "v %f %f %f",
                &positions[num_positions * 3 + 0],
                &positions[num_positions * 3 + 1],
                &positions[num_positions * 3 + 2]);
            num_positions++;
        }
        else if (!strncmp(line, "vt ", 3))
        {
            if (!material)
            {
                printf("No material being used\n");
                return false;
            }
            float u;
            float v;
            sscanf(line, "vt %f %f", &u, &v);
            const int x = u * (material->width - 1);
            const int y = v * (material->height - 1);
            const uint32_t i = (y * material->width + x) * material->channels;
            colours[num_colours * 3 + 0] = material->data[i + 0] / 255.0f;
            colours[num_colours * 3 + 1] = material->data[i + 1] / 255.0f;
            colours[num_colours * 3 + 2] = material->data[i + 2] / 255.0f;
            num_colours++;
        }
        else if (!strncmp(line, "vn ", 3))
        {
            sscanf(line, "vn %f %f %f",
                &normals[num_normals * 3 + 0],
                &normals[num_normals * 3 + 1],
                &normals[num_normals * 3 + 2]);
            num_normals++;
        }
        else if (!strncmp(line, "f ", 2))
        {
            sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                &faces[num_faces * 9 + 0],
                &faces[num_faces * 9 + 1],
                &faces[num_faces * 9 + 2],
                &faces[num_faces * 9 + 3],
                &faces[num_faces * 9 + 4],
                &faces[num_faces * 9 + 5],
                &faces[num_faces * 9 + 6],
                &faces[num_faces * 9 + 7],
                &faces[num_faces * 9 + 8]);
            num_faces++;
        }
    }
    mesh->size = num_faces * 3;
    mesh->vertices = malloc(sizeof(vertex_t) * mesh->size);
    if (!mesh->vertices)
    {
        printf("Failed to allocate vertices\n");
        return false;
    }
    for (uint32_t i = 0; i < num_faces * 3; i++)
    {
        vertex_t* vertex = &mesh->vertices[i];
        vertex->position.x = positions[(faces[i * 3 + 0] - 1) * 3 + 0];
        vertex->position.y = positions[(faces[i * 3 + 0] - 1) * 3 + 1];
        vertex->position.z = positions[(faces[i * 3 + 0] - 1) * 3 + 2];
        vertex->colour.r = colours[(faces[i * 3 + 1] - 1) * 3 + 0];
        vertex->colour.g = colours[(faces[i * 3 + 1] - 1) * 3 + 1];
        vertex->colour.b = colours[(faces[i * 3 + 1] - 1) * 3 + 2];
        vertex->normal.x = normals[(faces[i * 3 + 2] - 1) * 3 + 0];
        vertex->normal.y = normals[(faces[i * 3 + 2] - 1) * 3 + 1];
        vertex->normal.z = normals[(faces[i * 3 + 2] - 1) * 3 + 2];
    }
    for (uint32_t i = 0; i < num_materials; i++)
    {
        free(materials[i].data);
    }
    free(materials);
    free(positions);
    free(colours);
    free(normals);
    free(faces);
    fclose(file);
    return true;
}