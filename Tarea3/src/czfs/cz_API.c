#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "cz_API.h"


// void read_bin(char* data, int bloque, int bytes, int pass){
//   int size_bloque = 1024;
//   char* pathdata = "simdiskfilled.bin";
//   FILE* filebin;
//   filebin = fopen(pathdata, "rb");
//   fseek(filebin, bloque*size_bloque+pass, SEEK_SET);
//   fread(data, bytes, 1, filebin);
//   fclose(filebin);
// }

void bit_to_byte(int n, unsigned char* arr){
  for (int i = 0; i < n; i++){
    int output[CHAR_BIT];
    char c = arr[i];
    for (int j = 0; j < CHAR_BIT; ++j) {
      output[i] = (c >> i) & 1;
      printf("%c\n", c);
    }

    //int a = arr[i] - '0';
    //printf("0x%08x\n", a);
    int m = n-1-i;
    int b = pow(2, m);
  }
  printf("\n");
}

unsigned byte_to_decimal(int n, unsigned char* arr){
  unsigned decimalNumber = 0;
  char bin_arr[32];
  for (int i = 0; i < n; i++){
    char c = arr[i];
    static char bin[CHAR_BIT + 1] = {0};
    for (int j = CHAR_BIT - 1; j >= 0; j--){
      bin[j] = (c % 2) + '0';
      c /= 2;
      bin_arr[i*CHAR_BIT+j] = bin[j];
    }
    printf("%s\n", bin);

  }
  int a = bin_arr - '0';
  int m = n-1-i;
  int b = pow(2, m);
  decimalNumber += a*b;
  printf("\n");
  return decimalNumber;
}

int hexchar_to_dec(char value[4]){
  int dec;
  dec = value[0]*pow(16,6) + value[1]*pow(16,4) + value[2]*pow(16, 2) + value[3]*pow(16, 0);
  return dec;
}

int get_indice(char* filename){
  /* Se asume que se busca un archivo existente*/
  char bit_valid[1];
  char name[11];
  char indice[4];
  //bool found = false;
  char* pathdata = "simdiskfilled.bin";
  FILE* filebin;
  filebin = fopen(pathdata, "rb");
  fseek(filebin, 0, SEEK_CUR);
  for (int i = 0; i < 64; i++) {
    fread(&bit_valid, 1, 1, filebin);
    fread(&name, 11, 1, filebin);
    fread(&indice, 4, 1, filebin);
    if (bit_valid[0] == 1) {
      unsigned indice_int = byte_to_decimal(4, indice);
      // if (strncmp(name, filename, 11) == 0){
      //   //found = true;
      //   break;
      // }
    }
  }
  fclose(filebin);
<<<<<<< HEAD
  unsigned indice_int = byte_to_decimal(4, indice);
  //printf("0x%08x\n", indice);
  return indice_int;
=======
  //unsigned indice_int = binary_to_decimal(4, indice);
  return hexchar_to_dec(indice);
>>>>>>> master
}

czFILE* cz_open(char* filename, char mode){
  czFILE* file = malloc(sizeof(czFILE));
  unsigned indice;
  char r = 'r';
  char w = 'w';
  if (mode == r){
    file->open_mode = r;
    if (cz_exists(filename)) {
      indice = get_indice(filename);
      char* pathdata = "simdiskfilled.bin";
      FILE* filebin = fopen(pathdata, "rb");
      fseek(filebin, indice*64, SEEK_CUR);
      fread(file->size, 4, 1, filebin);
      fread(file->time_creat, 4, 1, filebin);
      fread(file->time_mod, 4, 1, filebin);
      fread(file->punteros_bloq_datos, 1008, 1, filebin);
      fread(file->indirect_pointer, 4, 1, filebin);
      fclose(filebin);
      return file;
    } else {
      return NULL;
    }
  }
  else if (mode == w) {
    if (!(cz_exists(filename))) {
      //go_on
    }
    else{
      return NULL;
    }
  }
  else {
    printf("Modo no válido");
    return NULL;
  }
  return NULL;
}

int cz_exists(char* filename){
  char bit_valid[1];
  char name[11];
  char indice[11];
  //unsigned char indice[4];
  char* pathdata = "simdiskfilled.bin";
  FILE* filebin;
  filebin = fopen(pathdata, "rb");
  fseek(filebin, 0, SEEK_CUR);
  for (int i = 0; i < 64; i++) {
    fread(bit_valid, 1, 1, filebin);
    fread(name, 11, 1, filebin);
    if (strncmp(name, filename, 11) == 0){
      //fread(indice, 4, 1, filebin);
      return 1;
    }
    fread(indice, 4, 1, filebin);
  }
  fclose(filebin);
  return 0;
}

int cz_read(czFILE* file_desc, void* buffer, int nbytes){
  return 0;
}

int cz_write(czFILE* file_desc, void* buffer, int nbytes){
  return 0;
}

int cz_close(czFILE* file_desc){
  return 0;
}

int cz_mv(char* orig, char *dest){
  return 0;
}

int cz_cp(char* orig, char* dest){
  return 0;
}

int cz_rm(char* filename){
  return 0;
}

void cz_ls(){
  char bit_valid[1];
  char name[11];
  unsigned char indice[4];
  //bool found = false;
  char* pathdata = "simdiskfilled.bin";
  FILE* filebin;
  filebin = fopen(pathdata, "rb");
  fseek(filebin, 0, SEEK_SET);
  for (int i = 0; i < 64; i++) {
    fseek(filebin, 0, SEEK_CUR);
    fread(bit_valid, 1, 1, filebin);
    fread(name, 11, 1, filebin);
    if (bit_valid[0] == 1) {
      printf("%s\n", name);
    }
    fread(indice, 4, 1, filebin);
  }
  fclose(filebin);
}
