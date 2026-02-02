#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
typedef __int64 ssize_t;

ssize_t getline(char** lineptr, size_t* n, FILE* stream) {
    if (*lineptr == NULL || *n == 0) {
        *n = 128;
        *lineptr = malloc(*n);
        if (*lineptr == NULL) return -1;
    }

    char* result = fgets(*lineptr, (int)*n, stream);
    if (result == NULL) return -1;
    
    size_t len = strlen(*lineptr);

    while (len > 0 && (*lineptr)[len - 1] != '\n' && !feof(stream)) {
        *n *= 2;
        char* new_ptr = realloc(*lineptr, *n);
        if (new_ptr == NULL) return -1;
        *lineptr = new_ptr;
        if (fgets(*lineptr + len, (int)(*n - len), stream) == NULL) break;
        len = strlen(*lineptr);
    }

    return (ssize_t)len;
}
#endif

typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
  if (input_buffer == NULL) {
    printf("Error allocating InputBuffer\n");
    exit(EXIT_FAILURE);
  }
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

void print_prompt() { printf("db > "); }

void read_input(InputBuffer* input_buffer) {
  ssize_t bytes_read =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  if (input_buffer->buffer == NULL) {
    printf("Error: input buffer is null after reading\n");
    exit(EXIT_FAILURE);
  }

  // Ignore trailing newline
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

int main(int argc, char* argv[]) {
  InputBuffer* input_buffer = new_input_buffer();
  while (true) {
    print_prompt();
    read_input(input_buffer);

    if (strcmp(input_buffer->buffer, ".exit") == 0) {
    if (input_buffer->buffer[0] == '.') {
      switch (do_meta_command(input_buffer)) {
        case (META_COMMAND_SUCCESS):
          continue;
          case (META_)
      }
    }
    }
  }
}