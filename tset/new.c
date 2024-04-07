#include "json_c.c"
#include <stdio.h>
#include <string.h>

typedef struct {
	char _nodetype[100];
    
} Ext;

typedef struct{
    char _nodetype[100];
} Type;

// 파일에서 JSON 데이터를 읽어오는 함수
char* read_json_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    fclose(file);

    buffer[length] = '\0';
    return buffer;
}

int main() {
    // 파일에서 JSON 데이터 읽어오기
    char* json_data = read_json_file("data.json");
    if (json_data == NULL) {
        return 1;
    }

    // JSON 데이터를 파싱하여 json_value 객체 생성
    json_value json_data_value = json_create(json_data);
    //json_print(json_data_value);
    json_value ext = json_get(json_data_value, "ext");
   
    int count=0;
    int ext_size = json_len(ext);
    printf("%d",ext_size);
    for(int i =0;i<ext_size;i++){
        printf("[%d] : ",i);
        printf("\n");
        json_value obj = json_get(ext,i);
        json_value type = json_get(obj,"type");
        char *s = json_get_string(type,"_nodetype");
        printf("%s\n",s);
        if (strcmp(s, "FuncDecl") == 0) {
            count++;
        }
        
        


    }
   // printf("%d = ",count);






    return 0;
}
