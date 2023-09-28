#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "External_Library/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "External_Library/stb_image_write.h"

struct image{
    char name[50];
    int height;
    int width;
}file[20];

struct node{
    char name[50];
    int height;
    int width;
    struct node *prev;
    struct node *next;
};

struct node *top;
struct node *first,*last;

void imageFile(){
    int width, height, channels;
    unsigned char *img = stbi_load("./Image/moon.jpg", &width, &height, &channels, 0);
    FILE *fp = fopen("imageFile.txt","a");
    if(img == NULL) {
        printf("Error in loading the image\n");
        exit(1);
    }
    printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);
    fprintf(fp,"%s#%d#%d\n","moon.jpg",height,width);
    fclose(fp);
}

int searchFile(char name[]){
    FILE *fp = fopen("imageFile.txt","r");
    int i = 0;
    while(fscanf(fp, "%[^#]#%d#%d\n",file[i].name, &file[i].width, &file[i].height) != EOF){
        if(strcmp(file[i].name,name) == 0){
            printf("File ditemukan\n");
            printf("Name: %s\n",name);
            printf("Width: %d px\n",file[i].width);
            printf("Height: %d px\n",file[i].height);
            return 0;
        }
        i++;
    }
    fclose(fp);
    return 1;

}

struct node *createNode(char name[], int height, int width){
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    strcpy(temp->name,name);
    temp->width = width;
    temp->height = height;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

void pushStack(char name[]) { 
    FILE *fp = fopen("imageFile.txt","r");
    int i = 0;
    while(fscanf(fp, "%[^#]#%d#%d\n",file[i].name, &file[i].width, &file[i].height) != EOF){
        if(strcmp(file[i].name,name) == 0){
            struct node *temp = createNode(file[i].name,file[i].height,file[i].width);
 
            if(!top) { 
                top = temp;
            }else { 
                top->prev = temp;
                temp->next = top;
                top = temp;
            }
        }
    }
    fclose(fp);
}

void pushQueue(char name[]) { 
    FILE *fp = fopen("imageFile.txt","r");
    int i = 0;
    while(fscanf(fp, "%[^#]#%d#%d\n",file[i].name, &file[i].width, &file[i].height) != EOF){
        if(strcmp(file[i].name,name) == 0){
            struct node *temp = createNode(file[i].name,file[i].height,file[i].width);
 
            if(!first) { 
                first = temp;
                last = temp;
            } else {
                last->next = temp;
                temp->prev = last;
                last = temp;
            }
        }
    }
    fclose(fp);
}

void removeStack() { 
    if(!top) { 
        return;
    } else if(top->next == NULL) { 
        free(top); 
        top = NULL; 
    } else { 
        struct node *newTop = top->next;
        top->next = NULL;
        newTop->prev = NULL;
        free(top);
        top = newTop;
    } 
}

void removeQueue() { 
    if(!first) { 
        return;
    } else if(first == last) { 
        free(first); 
        first = NULL;
        last = NULL; 
    } else { 
        struct node *newFirst = first->next;
        first->next = NULL;
        newFirst->prev = NULL;
        free(first);
        first = newFirst;
    } 
}

void printStack() {
    struct node *curr = top;
    puts("Stack: ");
    while(curr) {
        printf("|   Nama    |   Width    |  height  |\n");
        printf("  %s       %d px       %d px \n", curr->name, curr->width, curr->height);
        curr = curr->next; 
    }
    puts("NULL\n");
}

void printQueue() {
    struct node *curr = first;

    printf("Queue: \n");
    while(curr) {
        printf("|  Nama    |   Width    |  height  |\n");
        printf("  %s       %d px      %d px\n", curr->name, curr->width, curr->height);
        curr = curr->next; 
    }
    puts("NULL\n");
}

int main() {
    system("cls");
    int ch,n;
    char nama[20];
    char next;
    while(1){
        puts("MENU");
        printf("1.Search File\n2.Push Stack\n3.Push Queue\n4.Remove Stack\n5.Remove Queue\n");
        printf("6.Display Data Structur\n");
        printf(">> ");
        scanf("%d",&ch); getchar();
        switch (ch){
            case 1:
                printf("Masukan nama file: ");
                scanf("%s",nama); getchar();
                n = searchFile(nama);
                if(n == 1){
                    printf("File tidak ditemukan\n");
                }
                printf("\n\nPress Enter...");
                scanf("%c", next); getchar();
                system("cls");
            break;

            case 2:
                printf("Masukan nama file: ");
                scanf("%s",nama); getchar();
                pushStack(nama);
                printf("\n\nPress Enter...");
                scanf("%c", next); getchar();
                system("cls");
            break;       
            
            case 3:
                printf("Masukan nama file: ");
                scanf("%s",nama); getchar();
                pushQueue(nama);
                printf("\n\nPress Enter...");
                scanf("%c", next); getchar();
                system("cls");
            break;

            case 4:
                removeStack();
                printf("Remove berhasil dilakukan\n\n");
                printf("\nPress Enter...");
                scanf("%c", next); getchar();
                system("cls");
            break;
            
            case 5:
                removeQueue();
                printf("Remove berhasil dilakukan\n\n");
                printf("\nPress Enter...");
                scanf("%c", next); getchar();
                system("cls");
            break;

            case 6:
                printf("\n");
                printStack();
                printQueue();
                printf("\nPress Enter...");
                scanf("%c", next); getchar();
                system("cls");
                break;
        
        default:
            printf("Input salah");
            printf("\nPress Enter...");
            scanf("%c", next); getchar();
            system("cls");
            break;
        }
    }
}