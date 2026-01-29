#include <stdio.h>

#define HEADER_1 "----------------------------------------STUDENT----------------------------------------\n"
#define HEADER_2 " |\tnumber\t|\tname\t|\tComp\t|\tMath\t|\tEng\t|\tsum\t|\tave\t|\tmici\t|\n"
#define FORMAT " |\t%-10s\t|\t%-15s\t|\t%4d\t|\t%4d\t|\t%4d\t|\t%4d\t|\t%.2f\t|\t%4d\t|\n"
#define DATA p->data.num, p->data.name, p->data.cGrade, p->data.mGrade, p->data.eGrade, p->data.total, p->data.ave, p->data.mingCi
#define END "----------------------------------------END----------------------------------------\n"

// 是否保存
int saveFlag = 0;

struct Student {
    // 编号
    char num[10];
    // 姓名
    char name[15];
    // C 语言成绩
    int cGrade;
    // 数学成绩
    int mGrade;
    // 英语成绩
    int eGrade;
    // 总成绩
    int total;
    // 平均成绩
    float ave;
    // 名次
    int mingCi;
};

// 定义链表
typedef struct Node {
    struct Student data;
    struct Node *next;
} Node, *Link;


/**
 * 打印菜单
 */
void menu() {
    // 清理屏幕
    printf("育英中学成绩管理系统\n");
    printf("****************************************Menu****************************************\n");
    printf("1 input record                                                  2 delete reocrd\n");
    printf("3 search record                                                 4 modify record\n");
    printf("5 insert record                                                 6 count record\n");
    printf("7 sort record                                                   8 save record\n");
    printf("9 display record                                                10 quit system\n");
}

// 格式化输出表中数据
void print_data(Node* pp) {
    Node* p;
    p = pp;
    printf(FORMAT, DATA);
}

// 输出错误信息
void wrong() {
    printf("****************************************Error:input has wrong! press any key to continue.\n");
    getchar();
}

// 没有找到存储数据
void noFind() {
    printf("文件内容");
}

// 基于文件存储的增删改查文件

int main(void) {
    printf(HEADER_1);
    menu();
    return 0;
}

