//计算机系统基础实验1.1
//2022/9/26
//刘兴元
/*不同学生的备注长短不同，student结构比较占空间。
编写程序，将 old_s[3] 中的所有信息依次紧凑存放到一个字符数组中，
然后从 message 转换到结构数组 new_s[3]中。打印压缩前、解压后的结果，
以及压缩前、压缩后存放数据的长度。*/

#include<stdio.h>
#include<string.h>
struct student
{
    char  name[8];
    short age;
    float score;
    char  remark[200];  // 备注信息
};
student  old_s[3];    // old_s[0].name 为自己的姓名;
student  new_s[3];
char message[10086];

//s为结构数组的起始地址； sno 为学生人数； buf 为压缩区域存储区的首地址; 返回压缩后的字节数。
int pack_student_bytebybyte(student* s, int sno, char* buf);//实现一个字节一个字节的向buf中写数据
int pack_student_whole(student* s, int sno, char* buf);//要求对short、float字段都只能用一条语句整体写入，用strcpy实现串的写入。
int restore_student(char* buf, int len, student* s);

//第一个记录压缩（即old_s[0]）要调用pack_student_bytebybyte；第2-3个记录压缩要调用pack_student_whole。

//name 18 100.0 hello
//qqqq 20 88 swwyo

int main(void)
{
    int sno; //int i = 0;
    //scanf("%d", &sno);
    //for (int i = 0; i < 3; i++)
    //    scanf("%s%d%f%s", old_s[i].name, &old_s[i].age, &old_s[i].score, old_s[i].remark);
     /*初始化*/

    strcpy(old_s[0].name, "dzwwded");
    old_s[0].age = 18;
    old_s[0].score = 1002.533;
    strcpy(old_s[0].remark, "good");
    strcpy(old_s[1].name, "ltdz");
    old_s[1].age = 22;
    old_s[1].score = 1002.533;
    strcpy(old_s[1].remark, "nice");
    strcpy(old_s[2].name, "sc");
    old_s[2].age = 99;
    old_s[2].score = 0;
    strcpy(old_s[2].remark, "aha");

    for (int j = 0; j < 10086; j++) message[j] = '\0';
    int len1, len2;
    len1 = pack_student_bytebybyte(old_s, 1, message);
    len2 = pack_student_whole(old_s + 1, 2, message + len1);
    restore_student(message, len1 + len2, new_s);
    for (int j = 0; j < 3; j++)
        printf("%s %hd %f %s\n", new_s[j].name, new_s[j].age, new_s[j].score, new_s[j].remark);
    return 0;
}
int pack_student_bytebybyte(student* s, int sno, char* buf)
{
    int len = 0;
    for (int i = 1; i <= sno; i++)
    {
        char* p = s->name;
        while (*p != '\0')
        {
            *buf = *p;
            buf++; p++; len++;
        }
        *p = '\0'; len++; buf++;
        p = (char*)&s->age;
        *buf = *p; p++; buf++; len++;
        *buf = *p; p++; buf++; len++;
        p = (char*)&s->score;
        *buf = *p; p++; buf++; len++;
        *buf = *p; p++; buf++; len++;
        *buf = *p; p++; buf++; len++;
        *buf = *p; p++; buf++; len++;
        p = s->remark;
        while (*p != '\0')
        {
            *buf = *p;
            buf++; p++; len++;
        }
        *p = '\0'; len++;
    }
    return len;
}
int pack_student_whole(student* s, int sno, char* buf)
{
    int len = 0;
    for (int i = 1; i <= sno; i++)
    {
        char* p = s->name;
        strcpy(buf, p);
        buf += (strlen(p) + 1);
        len += (strlen(p) + 1);
        /*while (*p != '\0')
        {
            *buf = *p;
            buf++; p++; len++;
        }
        *p = '\0'; len++; buf++;*/
        p = (char*)&s->age;
        strncpy(buf, p, sizeof(char) * 2);
        len += 2; buf += 2;
        p = (char*)&s->score;
        strncpy(buf, p, sizeof(char) * 4);
        *(float*)buf = 
        len += 4; buf += 4;
        p = s->remark;
        strcpy(buf, p);
        buf += (strlen(p) + 1);
        len += (strlen(p) + 1);
        /*while (*p != '\0')
        {
            *buf = *p;
            buf++; p++; len++;
        }
        *p = '\0'; len++;
        s++; buf++;*/
        s++;
    }
    return len;
}
int restore_student(char* buf, int len, student* s)
{
    char* p;
    for (int i = 0; i < 3; i++)
    {
        p = s[i].name;

        while (*buf != '\0')
        {
            *p = *buf;
            p++; buf++;
        }
        *p = '\0'; buf++;

        p = (char*)&s[i].age;
        *p = *buf; buf++; p++;
        *p = *buf; buf++; p++;

        p = (char*)&s[i].score;
        *p = *buf; buf++; p++;
        *p = *buf; buf++; p++;
        *p = *buf; buf++; p++;
        *p = *buf; buf++; p++;

        p = s[i].remark;

        while (*buf != '\0')
        {
            *p = *buf;
            buf++; p++;
        }
        *p = '\0';
        buf++;
    }
    return 0;
}




