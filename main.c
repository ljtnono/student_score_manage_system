#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEADER_1 "----------------------------------------STUDENT----------------------------------------\n"
#define HEADER_2 " |\tnumber\t|\tname\t|\tComp\t|\tMath\t|\tEng\t|\tsum\t|\tave\t|\tmici\t|\n"
#define FORMAT " |\t%-10s\t|\t%-15s\t|\t%4d\t|\t%4d\t|\t%4d\t|\t%4d\t|\t%.2f\t|\t%4d\t|\n"
#define DATA p->data.num, p->data.name, p->data.cGrade, p->data.mGrade, p->data.eGrade, p->data.total, p->data.ave, p->data.mingCi
#define END "----------------------------------------END----------------------------------------\n"

// 是否保存标志
int saveFlag = 0;

struct Student {
    char num[10];      // 编号
    char name[15];     // 姓名
    int cGrade;        // C 语言成绩
    int mGrade;        // 数学成绩
    int eGrade;        // 英语成绩
    int total;         // 总成绩
    float ave;         // 平均成绩
    int mingCi;        // 名次
};

// 定义链表节点
typedef struct Node {
    struct Student data;
    struct Node *next;
} Node, *Link;

// 函数声明
void menu();
void print_data(Node* p);
void wrong();
void noFind();
void input_record(Node** head);
void delete_record(Node** head);
void search_record(Node* head);
void modify_record(Node* head);
void insert_record(Node** head);
void count_record(Node* head);
void sort_record(Node* head);
void save_record(Node* head);
void display_record(Node* head);
void load_record(Node** head);

// 使用SQLite驱动实现的函数
void add(struct Student student);
void delete(struct Student student);
void modify(struct Student student);
struct Student search(char* name);


/**
 * 打印菜单
 */
void menu() {
    printf("\n\n");
    printf("****************************************Menu****************************************\n");
    printf("1 input record                                                  2 delete record\n");
    printf("3 search record                                                 4 modify record\n");
    printf("5 insert record                                                 6 count record\n");
    printf("7 sort record                                                   8 save record\n");
    printf("9 display record                                                10 quit system\n");
    printf("************************************************************************************\n");
    printf("Please select an operation (1-10): ");
}

// 格式化输出表中数据
void print_data(Node* p) {
    printf(FORMAT, DATA);
}

// 输出错误信息
void wrong() {
    printf("\n****************************************Error: Input error! Press Enter to continue.\n");
    getchar();
    getchar(); // 消耗多余的换行符
}

// 没有找到存储数据
void noFind() {
    printf("\nData not found!\n");
}

// 录入记录
void input_record(Node** head) {
    Node* p, * tail;
    char ch;
    
    // 找到链表尾部
    tail = *head;
    while(tail && tail->next) {
        tail = tail->next;
    }
    do {
        p = (Node*)malloc(sizeof(Node));
        if (!p) {
            printf("Memory allocation failed!\n");
            return;
        }
        
        printf("Enter number: ");
        scanf("%s", p->data.num);
        // 检查重复学号
        Node *temp = *head;
        int exists = 0;
        while(temp) {
             if(strcmp(temp->data.num, p->data.num) == 0) {
                 printf("Error: Number %s already exists!\n", p->data.num);
                 free(p);
                 exists = 1;
                 break;
             }
             temp = temp->next;
        }
        if(exists) {
            printf("Continue to input? (y/n): ");
            getchar(); ch = getchar();
            continue;
        }

        printf("Enter name: ");
        scanf("%s", p->data.name);
        printf("Enter C Grade: ");
        scanf("%d", &p->data.cGrade);
        printf("Enter Math Grade: ");
        scanf("%d", &p->data.mGrade);
        printf("Enter English Grade: ");
        scanf("%d", &p->data.eGrade);
        
        p->data.total = p->data.cGrade + p->data.mGrade + p->data.eGrade;
        p->data.ave = (float)p->data.total / 3;
        p->data.mingCi = 0; // 排序后更新
        p->next = NULL;

        if (*head == NULL) {
            *head = p;
            tail = p;
        } else {
            tail->next = p;
            tail = p;
        }
        saveFlag = 1;

        printf("Continue to input? (y/n): ");
        getchar(); // 消耗之前的换行
        ch = getchar();
    } while (ch == 'y' || ch == 'Y');
}

// 显示所有记录
void display_record(Node* head) {
    if (!head) {
        printf("\nNo records found!\n");
        return;
    }
    printf(HEADER_1);
    printf(HEADER_2);
    while (head) {
        print_data(head);
        head = head->next;
    }
    printf(END);
}

// 保存记录到文件
void save_record(Node* head) {
    FILE* fp;
    if ((fp = fopen("students.txt", "w")) == NULL) {
        printf("Cannot open file!\n");
        return;
    }
    while (head) {
        fprintf(fp, "%s %s %d %d %d %d %.2f %d\n", 
            head->data.num, head->data.name, head->data.cGrade, 
            head->data.mGrade, head->data.eGrade, head->data.total, 
            head->data.ave, head->data.mingCi);
        head = head->next;
    }
    fclose(fp);
    printf("Saved successfully!\n");
    saveFlag = 0;
}

// 从文件加载记录
void load_record(Node** head) {
    FILE* fp;
    Node* p, * tail = NULL;
    
    if ((fp = fopen("students.txt", "r")) == NULL) {
        // 文件不存在则不加载
        return;
    }

    while (!feof(fp)) {
        p = (Node*)malloc(sizeof(Node));
        if (fscanf(fp, "%s %s %d %d %d %d %f %d", 
            p->data.num, p->data.name, &p->data.cGrade, 
            &p->data.mGrade, &p->data.eGrade, &p->data.total, 
            &p->data.ave, &p->data.mingCi) != 8) {
            free(p);
            break;
        }
        p->next = NULL;
        if (*head == NULL) {
            *head = p;
            tail = p;
        } else {
            tail->next = p;
            tail = p;
        }
    }
    fclose(fp);
}

// 统计记录
void count_record(Node* head) {
    int count = 0;
    if (!head) {
        printf("\nNo records!\n");
        return;
    }
    while (head) {
        count++;
        head = head->next;
    }
    printf("\nTotal records: %d\n", count);
}

// 排序记录 (交换数据域法)
void sort_record(Node* head) {
    Node *p, *q;
    struct Student temp;
    if (!head) {
        printf("No data to sort.\n");
        return;
    }
    
    // 冒泡排序链表版
    for (p = head; p != NULL; p = p->next) {
        for (q = p->next; q != NULL; q = q->next) {
            if (p->data.total < q->data.total) { // 降序
                temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }

    // 更新名次
    int rank = 1;
    for (p = head; p != NULL; p = p->next) {
        p->data.mingCi = rank++;
    }
    
    printf("Sorted successfully! Please display to view.\n");
    saveFlag = 1;
}

// 插入记录 (功能类似Input，但通常用于插入到特定位置，这里简化为追加或按Input逻辑)
void insert_record(Node** head) {
    input_record(head);
}

// 删除记录
void delete_record(Node** head) {
    char num[10];
    Node *p, *prev = NULL;
    
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    printf("Enter student number to delete: ");
    scanf("%s", num);
    
    p = *head;
    while (p) {
        if (strcmp(p->data.num, num) == 0) {
            if (prev == NULL) {
                *head = p->next;
            } else {
                prev->next = p->next;
            }
            free(p);
            printf("Deleted successfully!\n");
            saveFlag = 1;
            return;
        }
        prev = p;
        p = p->next;
    }
    noFind();
}

// 查找记录
void search_record(Node* head) {
    char num[10];
    if (!head) {
        printf("List is empty.\n");
        return;
    }
    printf("Enter number to search: ");
    scanf("%s", num);
    
    while(head) {
        if (strcmp(head->data.num, num) == 0) {
            printf(HEADER_1);
            printf(HEADER_2);
            print_data(head);
            printf(END);
            return;
        }
        head = head->next;
    }
    noFind();
}

// 修改记录
void modify_record(Node* head) {
    char num[10];
    if (!head) {
        printf("List is empty.\n");
        return;
    }
    printf("Enter number to modify: ");
    scanf("%s", num);
    
    while(head) {
        if (strcmp(head->data.num, num) == 0) {
            printf("Found student %s. Enter new details.\n", head->data.name);
            printf("Enter name: ");
            scanf("%s", head->data.name);
            printf("Enter C Grade: ");
            scanf("%d", &head->data.cGrade);
            printf("Enter Math Grade: ");
            scanf("%d", &head->data.mGrade);
            printf("Enter English Grade: ");
            scanf("%d", &head->data.eGrade);
            
            head->data.total = head->data.cGrade + head->data.mGrade + head->data.eGrade;
            head->data.ave = (float)head->data.total / 3;
            // mingCi 需要重新排序更新， temporarily invalid
            
            printf("Modified successfully!\n");
            saveFlag = 1;
            return;
        }
        head = head->next;
    }
    noFind();
}


int main(void) {
    Link head = NULL;
    int choice;
    
    load_record(&head); // 加载数据
    
    while (1) {
        menu();
        if (scanf("%d", &choice) != 1) {
             wrong();
             while(getchar() != '\n'); // 清除输入缓冲
             continue;
        }

        switch (choice) {
            case 1: input_record(&head); break;
            case 2: delete_record(&head); break;
            case 3: search_record(head); break;
            case 4: modify_record(head); break;
            case 5: insert_record(&head); break; 
            case 6: count_record(head); break;
            case 7: sort_record(head); break;
            case 8: save_record(head); break;
            case 9: display_record(head); break;
            case 10: 
                if (saveFlag) {
                    char ch;
                    printf("Data modified but not saved. Save now? (y/n): ");
                    getchar(); ch = getchar();
                    if (ch == 'y' || ch == 'Y') {
                        save_record(head);
                    }
                }
                printf("Goodbye!\n");
                return 0;
            default: wrong(); break;
        }
    }
    return 0;
}
