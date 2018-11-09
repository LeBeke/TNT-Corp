#include "matrix01.h"
 // recupère une image déja binarisée pour ensuite créer une matrice de 1 et de 0 et retourner cette dernière

SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}





int **frompicturetomatrix()
{
    SDL_Surface* image_surface;
    Uint8 r,g,b;
    SDL_Init(SDL_INIT_VIDEO);
    image_surface = load_image("my_image1.jpg"); //doit load une image en noir et blanc
    int width = image_surface->w;
    int height = image_surface->h;
    int **matrix= malloc(width *sizeof(int *));

    for(int i=0;i<width;i++)
    {
        matrix[i]=malloc(height *sizeof(int *));
        for (int j=0;j<height;j++)
        {
            Uint32 pixel = get_pixel(image_surface, i, j);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            if (r==0)
            {
                matrix[i][j]=0;
                //printf("%d",matrix[i][j]); pour afficher la matrix de 0 et de 1
            }
            else
            {   
                matrix[i][j]=1;
                //printf("%d",matrix[i][j]); 
            }
        }
    }
    SDL_FreeSurface(image_surface);
    free(matrix);
    return matrix;
    
}

 
 
int main(void)
{
  frompicturetomatrix();
   return 0;
}
