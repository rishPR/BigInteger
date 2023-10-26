#ifndef BigInteger_H
#define BigInteger_H

#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct BigInteger
{
    struct node *l;
    int sign;
    int length;
};

void sign_rev(struct node *head);
struct BigInteger initialize(char *s);


struct BigInteger add(struct BigInteger a,struct BigInteger b);
struct BigInteger addi(struct BigInteger a,struct BigInteger b,int sign);
struct BigInteger addm(struct BigInteger a,struct BigInteger b,int sign);



struct BigInteger sub(struct BigInteger a,struct BigInteger b);

struct BigInteger mul(struct BigInteger a,struct BigInteger b);
struct BigInteger multiply(struct BigInteger a , struct BigInteger b ,int sign);

struct BigInteger div1(struct BigInteger a , struct BigInteger b );
struct BigInteger division(struct BigInteger a , struct BigInteger b , int sign , int choice);
void divi(struct node *p1 ,struct node *p2 ,struct node *p3 ,int *l );
void divs(struct node *p1 ,struct node *p2 ,struct node *p3 );
int compare(struct BigInteger h1 , struct BigInteger h2);
int check_sub(struct node *h1 , struct node *h2);


void display(struct BigInteger c);
void print(struct node *head);

void turn(struct BigInteger dev);

void dump(struct BigInteger c);

struct BigInteger mod(struct BigInteger a , struct BigInteger b);
//struct BigInteger mod_sub(struct BigInteger a , struct BigInteger b);
#endif 
