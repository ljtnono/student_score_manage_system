#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HEADER_1 "----------------------------------------STUDENT----------------------------------------\n"
#define HEADER_2 " |\tnumber\t|\tname\t|\tComp\t|\tMath\t|\tEng\t|\tsum\t|\tave\t|\tmici\t|\n"
#define FORMAT " |\t%-10s\t|\t%-15s\t|\t%4d\t|\t%4d\t|\t%4d\t|\t%4d\t|\t%.2f\t|\t%4d\t|\n"
#define DATA p->data.num, p->data.name, p->data.cGrade, p->data.mGrade, p->data.eGrade, p->data.total, p->data.ave, p->data.mingCi
#define END "----------------------------------------END----------------------------------------\n"


int saveFlag = 0;

struct Student {
    // 编号
    char num[10];
    // 姓名
    char name[15];
    // C 语言成绩
    int cGrade;
    //
    int mGrade;
    int eGrade;
    int total;
    float ave;
    int mingCi;
};

// 定义链表
typedef struct node {
    struct student *data;
    struct node *next;
} Node, *Link;


/**
 * 打印菜单
 */
void menu() {

}


int main(void) {
    return 0;
}

