#include"BigInteger.h"



void sign_rev(struct node *head)
{
    if(head==0)return;
    head->data *= -1;
    sign_rev(head->next);
}

struct BigInteger initialize(char *s)
{
    struct BigInteger result;
    result.l = 0;
    result.length = 0;
    struct node *head = 0;
    int i = 0, j = 0, sign = 1;
    if (s[i] == '-')
    {
        sign = -1;
        i++;
    }
    result.sign = sign;

    while (s[i] != '\n' && s[i] != '\0')
    {
        if (s[i] != '0')
            break;
        i++;
    }
    while (s[i] != '\n' && s[i] != '\0')
    {
        struct node *temp = (struct node *)malloc(sizeof(struct node));
        if (!temp)
        {
            printf("Memory Allocation failed\n");
            return result;
        }
        temp->data = s[i] - '0';
        temp->next = 0;
        if (!head)
        {
            head = temp;
        }
        else
        {
            temp->next = head;
            head = temp;
        }
        i++;
        j++;
    }
    result.l = head;
    result.length = j;

    return result;
}

struct BigInteger add(struct BigInteger a,struct BigInteger b)
{
    if(a.sign == 1 && b.sign == 1 )
    {
        if(compare(a,b) == -1)
        return addi(b,a,1);
        return addi(a,b,1);
    }
    else if(a.sign == -1 && b.sign == 1)
    {
        if(compare(a,b) == -1)
        return addm(b,a,1);
        
        return addm(a,b,-1);
    }
    else if(a.sign == 1 && b.sign == -1)
    {
        if(compare(a,b) == -1)
        return addm(b,a,-1);

        return addm(a,b,1);
    }
    else if(a.sign == -1 && b.sign == -1)
    {
        if(compare(a,b) == -1)
        return addi(b,a,-1);
        return addi(a,b,-1);
    }
}

struct BigInteger addi(struct BigInteger a,struct BigInteger b , int sign)
{
    struct BigInteger dev;
    dev.sign=sign;
    dev.length=a.length;
    dev.l=0;
    struct node *head=0 , *p1=a.l , *p2=b.l, *itr , *temp;
    int num,carry=0;
    
    while(p2)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return dev;
        }

        num=p1->data+p2->data+carry;

        temp->data=num%10;
        carry=num/10;

        temp->next=0;
        if(!head)
        {
            head=temp;
            itr=head;
        }
        else
        {
            itr->next=temp;
            itr=temp;
        }
        p1=p1->next;
        p2=p2->next;
    }
    while(p1)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return dev;
        }
        temp->data=p1->data+carry;
        if(temp->data>0)
        {
            carry=temp->data/10;
            temp->data=temp->data%10;  
        }
        else
        {
            carry=0;
        }
        temp->next=0;
        if(!head)
        {
            head=temp;
            itr=head;
        }
  
        itr->next=temp;
        itr=temp;
        p1=p1->next; 
    }
    if(carry!=0)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return dev;
        }
        dev.length+=1;
        itr->next=temp;
        temp->data=carry;
        temp->next=0;
    }
    dev.l=head;
    turn(dev);
    return dev;
}

struct BigInteger addm(struct BigInteger a, struct BigInteger b,int sign)
{
    struct BigInteger dev;
    dev.sign=sign;
    dev.l=0;
    dev.length=a.length;
    struct node *head=0 , *p1=a.l , *p2=b.l ,*temp , *itr;
    int num,carry=0;
    sign_rev(p2);
   
    while(p2)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return dev;
        }

        num=p1->data+p2->data+carry;
        
        if(num<0)
        {
            temp->data=num+10;
            carry=-1;
        }
        else
        {
            temp->data=num;
            carry=0;
        }
        
        temp->next=0;
        if(!head)
        {
            head=temp;
            itr=head;
        }
        else
        {
            itr->next=temp;
            itr=temp;
        }
        p1=p1->next;
        p2=p2->next;
    }
    while(p1)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return dev;
        }
        temp->data=p1->data+carry;
        if(temp->data<0)
        {
            temp->data=temp->data+10;
            carry=-1;
        }
        else
        {
            carry=0;
        }
        
        temp->next=0;
        if(!head)
        {
            itr=head=temp;
        }
  
        itr->next=temp;
        itr=temp;
        p1=p1->next; 
    }
    dev.l=head;
    sign_rev(b.l);
    turn(dev);
    return dev;
}

void turn(struct BigInteger dev)
{
    struct node *tempfront=0,*itr=dev.l;
    if(!dev.l)
        return;
    while(itr->next)
    {
        if(itr->next->data==0 && tempfront==0)
        {
            tempfront=itr;
            itr=itr->next;
            continue;
        }
        if(itr->data!=0 && tempfront)
        {
            tempfront=0;
        }  
        itr=itr->next;
    }
    if(itr->data!=0)
    {
        tempfront=0;
    }

    if(tempfront)
    {
        itr=tempfront;
        tempfront=tempfront->next;
        itr->next=0;
        while(tempfront)
        {
            itr=tempfront;
            tempfront=tempfront->next;
            free(itr);
            dev.length -=1;
        }
    }
    
}



void display(struct BigInteger c)
{
    struct node *itr=c.l,*temp;
    if(!itr)
    {
        printf("0\n");
        return;
    }
    if(c.sign==-1 && itr->data || itr->next && c.sign==-1)
    {
        printf("-");
    }
    print(c.l);
    printf("\n");
}

void print(struct node *head)
{
    if(!head)
    {
        return;
    }
    print(head->next);
    printf("%d",head->data);
}


struct BigInteger sub(struct BigInteger a,struct BigInteger b)
{
    if(a.sign == 1 && b.sign == 1)
    {
        if(compare(a,b) == -1)
        return addm(b,a,-1);
      
        return addm(a,b,1);
    }
    else if(a.sign == -1 && b.sign == 1)
    {
        if(compare(a,b) == -1)
        return addi(b,a,-1);
        return addi(a,b,-1);
    }
    else if(a.sign == 1 && b.sign == -1)
    {
        if(compare(a,b) == -1)
        return addi(b,a,1);
        return addi(a,b,1);
    }
    else if(a.sign == -1 && b.sign == -1)
    {
        if(compare(a,b) == -1)
        return addm(b,a,1);
        
        return addm(a,b,-1);
    }
}


struct BigInteger mul(struct BigInteger a,struct BigInteger b)
{
    if(!a.l || !b.l)
    {
        struct BigInteger temp = {0 ,0 ,0};
        return temp;
    }
    if(a.sign == 1 && b.sign == 1 || a.sign == -1 && b.sign == -1)
    {
        return multiply(a,b,1);
    }
    else
    {
        return multiply(a,b,-1);
    }
    
}
struct BigInteger multiply(struct BigInteger a, struct BigInteger b, int sign)
{
    struct BigInteger result;
    result.l = 0;
    result.sign = sign;
    struct node *itrFront, *pt2, *itr, *head = 0, *p1 = a.l, *p2 = b.l;
    int i, num, carry, n = a.length + b.length;
    result.length = n;
    for (i = 1; i <= n; i++)
    {
        struct node *temp = (struct node *)malloc(sizeof(struct node));
        if (!temp)
        {
            printf("Memory Allocation failed\n");
            return result;
        }
        temp->data = 0;
        temp->next = 0;
        if (!head)
        {
            head = temp;
        }
        else
        {
            temp->next = head;
            head = temp;
        }
    }
    result.l = head;

    itr = itrFront = head;

    while (p1)
    {
        pt2 = p2;
        carry = 0;
        while (pt2)
        {
            num = (p1->data) * (pt2->data) + carry;

            itr->data += num;
            carry = (itr->data) / 10;
            itr->data = (itr->data) % 10;

            pt2 = pt2->next;
            itr = itr->next;
        }
        if (!pt2 && carry > 0)
        {
            itr->data += carry;
        }
        itrFront = itrFront->next;
        itr = itrFront;
        p1 = p1->next;
    }
    turn(result);
    return result;
}


void dump(struct BigInteger c)
{
    struct node *temp;
    while(c.l)
    {
        temp=c.l;
        c.l=c.l->next;

        free(temp);
    }
    c.l=0;
}



struct BigInteger div1(struct BigInteger a , struct BigInteger b )
{
    struct BigInteger temp ={0 , 0 , 0};
    if(!b.l || !a.l)
    {
        printf("Invalid input\n");
        return temp;
    }
    if(compare(a,b) == -1)
    {
        return temp;
    }
    else
    {
        if(a.sign == 1 && b.sign == 1 || a.sign == -1 && b.sign == -1)
        {
            
            return division(a,b,1,1);
            
        }
        else
        {
            return division(a,b,-1,1);
        }
    }
}

struct node *dup(struct node *head)
{
    struct node *h1=0,*itr, *temp;
    while(head)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return h1;
        }
        temp->data=head->data;
        temp->next=0;
        if(!h1)
        {
            h1=temp;
            itr=temp;
        }
        else
        {
            itr->next=temp;
            itr=temp;
        }
        head=head->next;
    }
    return h1;
}

struct BigInteger division(struct BigInteger a, struct BigInteger b, int sign, int choice)
{
    struct BigInteger result;
    result.l = 0;
    result.length = 0;
    result.sign = sign;
    int comp, length = b.length;
    struct node *head = 0, *itr, *temp_node, *p2 = b.l, *head_quotient = (struct node *)malloc(sizeof(struct node));
    if (!head_quotient)
    {
        printf("Memory allocation failed\n");
        return result;
    }

    if ((comp = compare(a, b)) < 1)
    {
        if (comp == 0)
        {
            if (choice == 0)
            {
                result.l = dup(a.l);
                return result;
            }
            head_quotient->data = 1;
            head_quotient->next = 0;
            result.l = head_quotient;
            result.length = 1;
            return result;
        }
        if (choice == 0)
        {
            result.l = dup(a.l);
            return result;
        }
        return result;
    }

    head = dup(p2);

    head_quotient->data = 1;
    head_quotient->next = 0;
    result.length = 1;
    while (a.length >= length + 1)
    {
        itr = (struct node *)malloc(sizeof(struct node));
        temp_node = (struct node *)malloc(sizeof(struct node));
        if (!temp_node && !itr)
        {
            printf("Memory allocation failed\n");
            return result;
        }
        temp_node->data = itr->data = 0;
        temp_node->next = head;
        head = temp_node;
        itr->next = head_quotient;
        head_quotient = itr;
        length += 1;
    }

    result.l = head;
    result.length = length;
    if ((comp = compare(a, result)) == -1)
    {
        temp_node = head;
        head = head->next;
        free(temp_node);
        temp_node = head_quotient;
        head_quotient = head_quotient->next;
        free(temp_node);
        length -= 1;
    }
    while (a.length > length)
        divi(head, b.l, head_quotient, &length);

    result.l = head;
    result.length = length;
    while ((comp = compare(a, result)) != -1 && comp != 0)
    {
        divi(head, b.l, head_quotient, &result.length);
    }

    if (comp == 0)
    {
        if (choice == 0)
        {
            result.l = head_quotient;
            dump(result);
            result.l = head;
            result.length = a.length;
            return result;
        }
        result.l = head;
        dump(result);
        result.l = head_quotient;
        result.length = length;
        return result;
    }
    if (compare(a, result) == -1)
    {
        divs(head, b.l, head_quotient);

        turn(result);
    }
    if (choice == 0)
    {
        result.l = head_quotient;
        dump(result);
        result.l = head;
        result.length = a.length;
        turn(result);
        return result;
    }
    result.l = head;
    dump(result);
    result.l = head_quotient;
    turn(result);
    return result;
}


int compare(struct BigInteger h1 , struct BigInteger h2)
{
    if(h1.length < h2.length)
        return -1;
    else if(h1.length > h2.length)
        return 1;
    else
    return check_sub(h1.l,h2.l);
}


int check_sub(struct node *h1 , struct node *h2)
{
    static int x;
    x=0;

    
    if(!h1 && !h2)
    {
        return x;
    }
    check_sub(h1->next,h2->next);
    
    if(x==-1)
        return x;
    else if(h1->data>h2->data)
    {
        x=1;
    }
    else if(h1->data<h2->data && x==0)
    {
        x=-1;
    }
    
    return x;

}


void divi(struct node *p1 ,struct node *p2 ,struct node *p3 , int *l)
{
    struct node *temp=0 ,*ptr;
    int num,carry=0;
    while(p2)
    {

        p1->data=p1->data+p2->data+carry;
        carry=(p1->data)/10;
        p1->data=(p1->data)%10;

        if(p1->next==0)
        {
            ptr=p1;
        }
        p1=p1->next;
        p2=p2->next;
    }
    while(p1)
    {
        if(p1->next==0)
        {
            ptr=p1;
        }
        p1->data=p1->data+carry;
        carry=(p1->data)/10;
        p1->data=(p1->data)%10;
       
        if(carry==0)
        {
            break;
        }
        p1=p1->next; 
    }
    if(carry!=0)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return;
        }
        ptr->next=temp;
        temp->data=carry;
        temp->next=0;
        *l+=1;
    }
    carry=1;
    while(p3)
    {
        p3->data=p3->data+carry;
        carry=(p3->data)/10;
        p3->data=(p3->data)%10;
        p3=p3->next;
        if(carry==0)
        {
            return;
        }
        if(p3->next==0)
        {
            ptr=p3;
        }
    }
    if(carry!=0)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return;
        }
        ptr->next=temp;
        temp->data=carry;
        temp->next=0;
        *l+=1;
    }
    
}
void dummy(){
    int i;
    for(i=0;i<10;i++)
    {
        printf("%d\n",i);
    }
}
void print_ll(){
    struct node *temp;
    temp=l;
    while(temp)
    {
        printf("%d\n",temp->data);
        temp=temp->next;
    }
}

void divs(struct node *p1 ,struct node *p2 ,struct node *p3 )
{
    struct node *ptr=p2;
    int num,carry=0;
    sign_rev(p2);
    
    while(p2)
    {
        p1->data=p1->data+p2->data+carry;
        
        if(p1->data<0)
        {
            p1->data=p1->data+10;
            carry=-1;
        }
        else
        {
            carry=0;
        }
        
        p1=p1->next;
        p2=p2->next;
    }
    while(p1)
    {
        p1->data=p1->data+carry;
        if(p1->data<0)
        {
            p1->data=p1->data+10;
            carry=-1;
        }
        else
        {
            carry=0;
        }
        if(carry==0)
        {
            break;
        }
        p1=p1->next;
         
    }
    sign_rev(ptr);

    carry=-1;
    while(p3)
    {
        p3->data=p3->data+carry;
        if(p3->data<0)
        {
            p3->data+=10;
            carry=-1;
        }
        else 
        {
            carry=0;
        }
        if(carry==0)
        {
            return;
        }
        p3=p3->next;
    }
}

struct BigInteger mod(struct BigInteger a , struct BigInteger b)
{
    struct BigInteger temp ={0 , 0 , 0};
    if(!b.l || !a.l)
    {
        printf("Invalid input\n");
        return temp;
    }
    if(compare(a,b)== -1)
    {
        temp.l=dup(a.l);
        temp.length=a.length;
        return temp;
    }
    else
    {
        if(a.sign == 1 && b.sign == 1 || a.sign == -1 && b.sign == -1)
        {
            
            temp= division(a,b,1,0);
            
        }
        else
        {
            temp = division(a,b,-1,0);
        }
    }
    if(compare(a,temp)==0)
    
    {
        temp.l=dup(a.l);
        temp.length=a.length;
        return temp;
    }
    return addm(a,temp,1);
}