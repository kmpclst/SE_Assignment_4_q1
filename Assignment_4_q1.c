#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct Inventory {
    int id;
    char productname[50];
    int quantity;
    float price;
    char date[12];
};

void addproduct() {
    struct Inventory iv;
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(iv.date, myDate);

    FILE *fp = fopen("product.txt", "a");
    if(fp == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Enter product id: ");
    scanf("%d", &iv.id);

    printf("Enter the product name: ");
    fflush(stdin);
    scanf("%s", iv.productname);

    printf("Enter product quantity: ");
    fflush(stdin);
    scanf("%d", &iv.quantity);

    printf("Enter the product price: ");
    fflush(stdin);
    scanf("%f", &iv.price);

    fprintf(fp, "%d %s %d %.2f %s\n", iv.id, iv.productname, iv.quantity, iv.price, iv.date);

    fclose(fp);
    printf("\nProduct added successfully...\n");
}

void displayproducts() {
    system("cls");
    printf("<=== Product List ===>\n\n");
    printf("%-10s %-30s %-30s %-20s %s\n", "Id", "Product Name", "Quantity", "Price", "Date");
    printf("\n---------------------------------------------------------------------------------------\n");

    FILE *fp = fopen("product.txt", "r");
    if(fp == NULL) {
        perror("Error opening file");
        return;
    }

    struct Inventory iv;
    while(fscanf(fp, "%d %s %d %f %s", &iv.id, iv.productname, &iv.quantity, &iv.price, iv.date) != EOF) {
        printf("%-10d %-30s %-30d %-20.2f %s\n", iv.id, iv.productname, iv.quantity, iv.price, iv.date);
    }
    fclose(fp);
}

void updateinventory() {
    int id, f = 0;
    system("cls");
    printf("<== Update products ==>\n\n");
    printf("Enter the product id to update: ");
    scanf("%d", &id);

    FILE *fp = fopen("product.txt", "r+");
    if(fp == NULL) {
        perror("Error opening file");
        return;
    }

    struct Inventory iv;
    FILE *ft = fopen("temp.txt", "w");
    if(ft == NULL) {
        perror("Error opening file");
        fclose(fp);
        return;
    }

    while(fscanf(fp, "%d %s %d %f %s", &iv.id, iv.productname, &iv.quantity, &iv.price, iv.date) != EOF) {
        if(id == iv.id) {
            f = 1;
            printf("select the operation to be performed\n");
            printf("1. update the product name\n");
            printf("2. update the quantity\n");
            printf("3. update the product price\n");
            int val;
            printf("enter your choice: ");
            scanf("%d", &val);

            switch(val) {
                case 1:
                    printf("Enter the product name: ");
                    fflush(stdin);
                    scanf("%s", iv.productname);
                    break;

                case 2:
                    printf("Enter product quantity: ");
                    fflush(stdin);
                    scanf("%d", &iv.quantity);
                    break;

                case 3:
                    printf("Enter the product price: ");
                    fflush(stdin);
                    scanf("%f", &iv.price);
                    break;

                default:
                    printf("invalid input\n");
            }

            fprintf(ft, "%d %s %d %.2f %s\n", iv.id, iv.productname, iv.quantity, iv.price, iv.date);
        } else {
            fprintf(ft, "%d %s %d %.2f %s\n", iv.id, iv.productname, iv.quantity, iv.price, iv.date);
        }
    }

    fclose(fp);
    fclose(ft);

    remove("product.txt");
    rename("temp.txt", "product.txt");

    if(f == 1) {
        printf("\nProduct updated...\n");
    } else {
        printf("\nProduct Not Found !!");
    }
}

void del(int id) {
    int f = 0;
    FILE *fp = fopen("product.txt", "r");
    FILE *ft = fopen("temp.txt", "w");

    if(fp == NULL || ft == NULL) {
        perror("Error opening file");
        return;
    }

    struct Inventory iv;
    while(fscanf(fp, "%d %s %d %f %s", &iv.id, iv.productname, &iv.quantity, &iv.price, iv.date) != EOF) {
        if(id == iv.id) {
            f = 1;
        } else {
            fprintf(ft, "%d %s %d %.2f %s\n", iv.id, iv.productname, iv.quantity, iv.price, iv.date);
        }
    }

    fclose(fp);
    fclose(ft);

    remove("product.txt");
    rename("temp.txt", "product.txt");
}

void deleteproduct() {
    int id, f;
    system("cls");
    printf("<== Delete Products ==>\n\n");
    printf("enter the product id to delete: ");
    scanf("%d", &id);

    FILE *fp = fopen("product.txt", "r");
    if(fp == NULL) {
        perror("Error opening file");
        return;
    }

    struct Inventory iv;
    while(fscanf(fp, "%d %s %d %f %s", &iv.id, iv.productname, &iv.quantity, &iv.price, iv.date) != EOF) {
        if(id == iv.id) {
            f = 1;
            break;
        }
    }

    fclose(fp);

    if(f == 1) {
        printf("product deleted successfully...\n");
        del(id);
    } else {
        printf("\n\nProduct Not Found !!");
    }
}

void administrator() {
    int val;
    printf("\n");
    printf("1. add product\n");
    printf("2. update inventory\n");
    printf("3. delete product\n");
    printf("4. display products\n");

    scanf("%d", &val);
    switch(val) {
        case 1:
            addproduct();
            break;
        case 2:
            updateinventory();
            break;
        case 3:
            deleteproduct();
            break;
        case 4:
            displayproducts();
            break;
        default:
            printf("invalid input\n");
    }
}

void buy() {
    int id, f = 0, quant;
    system("cls");
    printf("<== Buy products ==>\n\n");
    printf("enter the product id to buy: ");
    scanf("%d", &id);
    printf("enter the quantity of the product: ");
    scanf("%d", &quant);

    FILE *fp = fopen("product.txt", "r+");
    if(fp == NULL) {
        perror("Error opening file");
        return;
    }

    float p;
    struct Inventory iv;
    FILE *ft = fopen("temp.txt", "w");
    if(ft == NULL) {
        perror("Error opening file");
        fclose(fp);
        return;
    }

    while(fscanf(fp, "%d %s %d %f %s", &iv.id, iv.productname, &iv.quantity, &iv.price, iv.date) != EOF) {
        if(id == iv.id) {
            p = iv.price;
            if(iv.quantity - quant < 0) {
                printf("Insufficient quantity available\n");
                fclose(fp);
                fclose(ft);
                return;
            } else {
                f = 1;
                iv.quantity = iv.quantity - quant;
                fprintf(ft, "%d %s %d %.2f %s\n", iv.id, iv.productname, iv.quantity, iv.price, iv.date);
                if(iv.quantity == 0) {
                    continue;
                }
            }
        } else {
            fprintf(ft, "%d %s %d %.2f %s\n", iv.id, iv.productname, iv.quantity, iv.price, iv.date);
        }
    }

    fclose(fp);
    fclose(ft);

    remove("product.txt");
    rename("temp.txt", "product.txt");

    if(f == 1) {
        printf("<===== Here is the invoice =====>\n");
        printf("Total amount payable: %.2f\n", p * quant);
        printf("Product bought successfully...\n");
    } else {
        printf("Product Not Found !!\n");
    }
}

void customer() {
    int val;
    printf("1. buy product\n");
    printf("2. view product inventory\n");
    printf("enter the choice: ");
    scanf("%d", &val);

    switch(val) {
        case 1:
            buy();
            break;
        case 2:
            displayproducts();
            break;
        default:
            printf("invalid input\n");
    }
}

int main() {
    int val;

    while(1) {
        printf("1. Administator\n");
        printf("2. Customer\n");
        printf("0. Exit\n");
        printf("-->Enter your choice: ");
        scanf("%d", &val);

        switch(val) {
            case 1:
                administrator();
                break;
            case 2:
                customer();
                break;
            case 0:
                exit(0);
            default:
                printf("invalid input\n");
        }
    }

    return 0;
}