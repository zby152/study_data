#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node*next;
};
int main()
{
	int n,m;//���Ӹ�������������m�˳� 
	int i;
	int answer;//����ÿ�δ𰸣����ͳһ��� 
	int count=0;//count����������Ŀ�𰸵��±� 
	struct node *head,*tail,*p,*q;//pָ��ǰ����Ľڵ㣬q����ָ��pָ��ָ���ǰһ���ڵ� 
	
	//����ͷ�ڵ㣬Ϊ����debug���٣���������Ϊ-1
	head=(struct node*)malloc(sizeof(struct node));
	head->data=-1;
	head->next=NULL;
	
		scanf("%d%d",&n,&m);
		if(n==0||m==0){
			free(head);
			return 1; 
		}
		else{
			tail=head;
			for(i=0;i<n;i++){
				//����β�巨����ѭ��������tailָ��ָ�����һ���ڵ�
				p=(struct node*)malloc(sizeof(struct node));
				p->data=i+1;//��д������� 
				tail->next=p;//�嵽β�� 
				p->next=head->next; //���ڵ��next��ָ���һ����Ч�ڵ㣬�γ�ѭ������ 
				tail=p;//tail�ƶ������һ���ڵ㣬Ϊ��һ�β�����׼�� 
			}
			p=head->next;
			q=tail;
			i=1;
			while(q!=p){//p,q����һǰһ��һ��������������˵��ֻʣһ���ڵ��� 
				if(i==m){
					//�ѵ�ǰ�ڵ���б���ɾ��
					q->next=q->next->next;
					free(p);
					//��p�ƶ�����һ����Ч�ڵ��ϣ�i=1���¿�ʼ����
					p=q->next;
					i=1; 
				} 
				else{
					//p,q��������ƶ�һ���ڵ㣬����q������p��ǰ��
					q=p;
					p=p->next;
					//����+1
					i++; 
				}
			} 
			//head->next=q
			//ǰ��ɾ���ڵ�ʱ�������ֻʣ����������ʱ���п�����������������������Ŀ�����������Բ�Ҫ
			answer=p->data;
			free(p);
			head->next=NULL;//�����ѿգ�ֻ��ͷ�ڵ��ˣ���ͷ�ڵ��next��ֵΪNULL����Ȼ���Ǳ���ģ�ȷ�Ǻ�ϰ�� 
		}
	
		printf("%d\n",answer);
	 
	 free(head);
	 return 0;
}
