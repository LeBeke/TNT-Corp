#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"

void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}

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
SDL_Surface* display_image(SDL_Surface *img)
{
    SDL_Surface *screen;

    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (screen == NULL)
    {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
                img->w, img->h, SDL_GetError());
    }

    // Blit onto the screen surface
    if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    // return the screen for further uses
    return screen;
}

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}

void SDL_FreeSurface(SDL_Surface *surface);


int main()
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;

    // Initialize the SDL
    init_sdl();

    //Load image from a path 
    image_surface = load_image("my_image.jpg");

    // Display the image.
     screen_surface= display_image(image_surface);
    

    // Wait for a key to be pressed.
    wait_for_keypressed();

    /*  For each pixel of the image: 
        Get the pixel value.
        Get the RGB values of the pixel.
        Compute the weighted average of the RGB values:
        average = 0.3*r + 0.59*g + 0.11*b (greyscale value)
        If the average value is lower than 128: set it on 0 else on 255;
        Get the new pixel value from the new RGB values.
        Put the new pixel value on the surface.
    */
    Uint8 r, g, b;
    int width = image_surface->w;
    int height = image_surface->h;

    for (int x=0; x<width;x++)
    {
        for (int y =0;y<height;y++)
        {
            Uint32 pixel = get_pixel(image_surface, x, y);
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            Uint32 average= 0.3*r + 0.59*g + 0.11*b;
            if(average>128)
            {
                r=255;
                g=255;
                b=255;
            }
            else
            {
                r=0;
                g=0;
                b=0;
            }
            pixel= SDL_MapRGB(image_surface->format, r, g, b);
            put_pixel(image_surface, x, y, pixel);
        }
    }
    //update screen surface
    update_surface(screen_surface,image_surface);

    // Wait for a key to be pressed.
    wait_for_keypressed();

    // Free the image surface.
    SDL_FreeSurface(image_surface);
    
    // Free the screen surface.
    SDL_FreeSurface(screen_surface);
    
    return 0;
}