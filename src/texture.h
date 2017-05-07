typedef struct texture texture;

struct texture {
  SDL_Texture* texture;
  int width;
  int height;
};

texture* init_texture();
int loadTextureFromFile(texture* t, SDL_Renderer* r, const char* path);
void renderTexture(texture* t, SDL_Renderer* r, int x, int y, SDL_Rect* clip);
void freeTexture(texture* t);
