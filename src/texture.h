typedef struct texture texture;

struct texture {
  SDL_Texture* texture;
  int width;
  int height;
};

bool loadTextureFromFile(texture* t, SDL_Renderer* r, const char* path);
void renderTexture(texture* t, SDL_Renderer* r, int x, int y);
void freeTexture(texture* t);
