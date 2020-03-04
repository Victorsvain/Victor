#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h> 
int song_numbers;//�������и�����
int order_songs=0;//�û������ 
struct song{
	int num;
	char name[100];
	char singername[100];
	char spell[100];
	double score;
	int sumAccess;
	int state;   //1�������ۣ�0����δ������ 
};
struct Admin{
	char name[20];
	char password[20];	
	struct song AllSongList[200];
	struct song SongRank[200];
};
struct User{
	struct song WaitingList[200]; 
};
struct Admin a={"victor","victor12345"};
struct User user;
void createSonglibrary(Admin *now);
void ShowMain();
void ShowEnd();
void ShowUser();
void ShowAdmin(Admin *now);
void LoginAdmin(Admin *now,int count);
void newPassword(Admin *now,char key[20]);
void getPassword(Admin *now,char key[20]);
void viewAllsongs(Admin *now,int num,int page,int judge);
void addSong(Admin *now);
void addSongs(Admin *now);
int findSong(Admin *now,struct song newSong);
void sortSongs(Admin *now);
void viewSongRank(Admin *now,int num,int page);
void showChange(Admin *now);
//����ΪAdmin����
void addBySinger(User *user);
void addByName(User *user);
void addBySpell(User *user);
void FindSinger(Admin *now,char singer[100]);
void FindName(Admin *now,char name[100]);
void FindSpell(Admin *now,char spell[100]); 
void forSelected(User *user,Admin *now,int page,int num[50],int count,int flag); 
void viewSelected(User *user,int page,int flag);
void DeleteSong(User *user);
void ForRemoveSong(User *user);
void ForToTop(User *user);
void ForEvaluateSong(User *user);
void removeSong(User *user);
void toTop(User *user);
void evaluateSong(User *user,Admin *now);
void createSonglibrary(Admin *now){
	FILE *fp;
	fp=fopen("song.txt","r");
		fscanf(fp,"%d",&song_numbers);
    for(int i=0;i<song_numbers;i++)	
	{	char name[100];
		char singer[100];
		char spell[100];
		double score;
		fscanf(fp,"%s",&name);
		fscanf(fp,"%s",&singer);
		fscanf(fp,"%s",&spell);
		fscanf(fp,"%lf",&score); 
	    strcpy(now->AllSongList[i].name,name);
	    strcpy(now->AllSongList[i].singername,singer);
	    strcpy(now->AllSongList[i].spell,spell);
	    now->AllSongList[i].num=i+1;
	    now->AllSongList[i].score=score;
	    now->AllSongList[i].state=0;
		}
		fclose(fp);
}
void showMain(){
	system("cls");
	printf("      KTV���ϵͳ       \n");
	printf("===========================\n");
	printf("*      1 �û�ֱ��        *\n");
	printf("*      2 ����Ա��½      *\n");
	printf("*      3 �˳�ϵͳ        *\n"); 
	printf("===========================\n");
	printf("������ѡ���\n");
	int x;
	scanf("%d",&x);
	switch(x){
		case 1:ShowUser(); break;
		case 2:LoginAdmin(&a,0);break;
		case 3:ShowEnd();break;
		default:printf("\n���벻�Ϸ�\n");
		        printf("��ENTER����������...\n");
		        getchar();
		        showMain(); 
	} 
} 
void ShowEnd(){
	system("cls");
	printf("��л���Ĺ��٣���ӭ�´�������\n");
	printf("      ϵͳ�����˳�.........\n");
}
void LoginAdmin(Admin *now,int count){
	getchar();
	system("cls");
    printf("**********����Ա��½*************\n");
    printf("����ԱID��victor\n");
	printf("���룺\n");
	int x=0;
	char str[20]={'\0'};
	char ch;
    while(1){
		char ch=getch();
		if(ch!='\r'){
		str[x]=ch;
		x++;	
		printf("*");
		}else break;
	}
	char key[20]={'\0'};
	getPassword(now,key);
	if(strcmp(str,key)==0){
		system("cls");
		printf("��½�ɹ���ϵͳ�����Զ���ת......\n");
		ShowAdmin(now);
	}
	else{
		count++;
		if(count==3){
			system("cls");
			printf("�������������࣬ϵͳ�Զ�����.....\n");
			showMain(); 
		}
		else{
			system("cls");
			printf("\n�����������%d�Σ�����%d���������\n",count,3-count);
			LoginAdmin(now,count);
		}
	}
}
	
void ShowAdmin(Admin *now){
	system("cls");
	printf("      KTV����Աϵͳ       \n");
	printf("===========================\n");
	printf("*      1 ���и���        *\n");
	printf("*      2 ��Ӹ���        *\n");
	printf("*      3 �����������    *\n");
	printf("*      4 ��������        *\n");
	printf("*      5 �鿴��������    *\n"); 
	printf("*      6 �޸�����        *\n");
	printf("*      0 ��    ��        *\n");
	printf("������ѡ���\n");	
	int x;
	scanf("%d",&x);
	switch(x){
		case 1:viewAllsongs(now,song_numbers,1,0);break;
		case 2:addSong(now);break;
		case 3:addSongs(now);break;
		case 4:sortSongs(now);break;
		case 5:viewSongRank(now,song_numbers,1);break; 
		case 6:showChange(now);break;
		case 0:showMain();break;
		default:printf("\n���벻�Ϸ�\n");
		        printf("��ENTER����������...\n");
		        getchar();
		        ShowAdmin(now);
	}
}
void ShowUser(){
	system("cls");
	printf("      KTV�û�ϵͳ       \n");
	printf("===========================\n");
	printf("*      1 ���ֵ��        *\n");
	printf("*      2 �������        *\n");
	printf("*      3 ƴ�����        *\n");
	printf("*      4 ���и���        *\n");
	printf("*      5 �ѵ����        *\n");
	printf("*      6 ��    ��        *\n"); 
	printf("*      7 ɾ������        *\n");
	printf("*      8 �ö�����        *\n");
	printf("*      9 ��������        *\n");
	printf("*      0 ��    ��        *\n");
	printf("������ѡ���\n");	
	int x;
	scanf("%d",&x);
	switch(x){
		case 1:addBySinger(&user);break;
		case 2:addByName(&user);break;
		case 3:addBySpell(&user);break;
		case 4:viewAllsongs(&a,song_numbers,1,1);break;
		case 5:viewSelected(&user,1,0);break;
		case 6:DeleteSong(&user);break;
		case 7:ForRemoveSong(&user);break;
		case 8:ForToTop(&user);break;
		case 9:ForEvaluateSong(&user);break;
		case 0:showMain();break;
		default:printf("\n���벻�Ϸ�\n");
		        printf("��ENTER����������...\n");
		        getchar();
		        ShowUser();
		
	}
}
void viewAllsongs(Admin *now,int num,int page,int judge){
	getchar();
	int sum=num/10+1;
	system("cls");
	printf("���\t             ������\t              ������\t\n");
	printf("-------------------------------------------------\n");
	if(page==sum){
		for(int i=0;i<num%10;i++){
			int k=(sum-1)*10+i;
			printf("%d\t        ��%s��\t         %s\t",i+1,now->AllSongList[k].name,now->AllSongList[k].singername);
			printf("\n");
		}
	}
	else{
		for(int i=0;i<10;i++){
			int k=(page-1)*10+i;
			printf("%d\t        ��%s��\t         %s\t",i+1,now->AllSongList[k].name,now->AllSongList[k].singername);
			printf("\n");
		}
	}
	printf("��%dҳ����%dҳ����һҳ��w��,��һҳ��s��,����ENTER������ҳ\n",page,sum);  
	char ch;
	ch=getchar();
		if(ch=='w'){
			if(page<=1){
				printf("��ǰ�Ѿ�����ҳ������������\n");
				viewAllsongs(now,num,1,judge);
			}
			else{
			  page=page-1;
			  viewAllsongs(now,num,page,judge);
			}
		}
		else if(ch=='s'){
			if(page==sum){
				printf("��ǰ�Ѿ������һҳ������������\n");
				viewAllsongs(now,num,page,judge);
			}
			else{
				page=page+1;
				viewAllsongs(now,num,page,judge);
			}
		}
		else if(ch=='\n'){
			if(judge==0)
			ShowAdmin(now);
			else if(judge==1)
			ShowUser();
		}
}
void addSong(Admin *now){
	system("cls");
	printf("�����룺"); 
	printf("����\t\t����\t\tƴ��\n");
	printf("==========================\n");
	char name[100];
	char singer[100];
	char spell[100];
	struct song newSong;
	scanf("%s",&name);
	scanf("%s",&singer);
	scanf("%s",&spell);
	getchar();
	strcpy(newSong.name,name);
	strcpy(newSong.singername,singer);
    strcpy(newSong.spell,spell);
    if(findSong(now,newSong)==1){
    	system("cls");
    	printf("�ø����Ѿ�����\n");
    	printf("���ʧ��\n");
    	printf("��0����ԭ���棬��1������Ӹ���\n");
    	char ch=getchar();
    	getchar();
    	if(ch=='0'){
    		ShowAdmin(now);
		}
		else if(ch=='1'){
			addSong(now);
		}
	}
	else {
	  strcpy(now->AllSongList[song_numbers].name,name);
	  strcpy(now->AllSongList[song_numbers].singername,singer);
	  strcpy(now->AllSongList[song_numbers].spell,spell);
	  now->AllSongList[song_numbers].num=1+song_numbers;
	  now->AllSongList[song_numbers].score=0;
	  now->AllSongList[song_numbers].state=0;
	  song_numbers++;
      printf("������ӳɹ���\n");
      printf("��0����ԭ���棬��1������Ӹ���\n");
      char ch=getchar();
      getchar();
      if(ch=='0'){
      	ShowAdmin(now);
	  }
	  else if(ch=='1'){
	  	addSong(now);
	  }
	} 
}
void addSongs(Admin *now){
	system("cls");
	printf("1.songlist_1.txt\n");
	printf("2.songlist_2.txt\n");
	printf("��ѡ��Ҫ����ĸ赥\n");
	int x;
	scanf("%d",&x);
	getchar(); 
	FILE *fp;
	if(x==1)
	fp=fopen("songlist_1.txt","r");
    if(x==2)
	fp=fopen("songlist_2.txt","r");
	int addnum=0;
	fscanf(fp,"%d",&addnum);
	for(int i=0;i<addnum;i++){
    	char name[100];
		char singer[100];
		char spell[100];
		fscanf(fp,"%s",&name);
		fscanf(fp,"%s",&singer);
		fscanf(fp,"%s",&spell);
		struct song newSong;
		strcpy(newSong.name,name);
    	strcpy(newSong.singername,singer);
        strcpy(newSong.spell,spell);
        if(findSong(now,newSong)==0){
	    strcpy(now->AllSongList[song_numbers].name,newSong.name);
	    strcpy(now->AllSongList[song_numbers].singername,newSong.singername);
	    strcpy(now->AllSongList[song_numbers].spell,newSong.spell);
	    now->AllSongList[song_numbers].num=1+song_numbers;
	    now->AllSongList[song_numbers].score=0;
	    now->AllSongList[song_numbers].state=0;
	    song_numbers++;
		}	
	} 
	fclose(fp);
	system("cls");
	printf("������ӳɹ���\n");
	printf("��0������һ����,��1�˳�ϵͳ\n");
	char ch=getchar();
	getchar();
	if(ch=='0')
	ShowAdmin(now);
	else if(ch=='1')
	ShowEnd(); 
}
int findSong(Admin *now,struct song newSong){
	int i;
	for(i=0;i<song_numbers;i++){
		if(strcmp(now->AllSongList[i].name,newSong.name)==0&&
		strcmp(now->AllSongList[i].singername,newSong.singername)==0&&
		strcmp(now->AllSongList[i].spell,newSong.spell)==0)
		return 1;
	}
	return 0;
}
void sortSongs(Admin *now){
	int i,j;
	for(i=0;i<song_numbers;i++){
		strcpy(now->SongRank[i].name,now->AllSongList[i].name);
		strcpy(now->SongRank[i].singername,now->AllSongList[i].singername);
		strcpy(now->SongRank[i].spell,now->AllSongList[i].spell);
		now->SongRank[i].score=now->AllSongList[i].score; 
	}
	for(i=0;i<song_numbers-1;i++){
		for(j=i+1;j<song_numbers;j++){
			if(now->SongRank[j].score<now->SongRank[i].score){
				struct song temp;
				strcpy(temp.name,now->SongRank[j].name);
				strcpy(temp.singername,now->SongRank[j].singername);
				strcpy(temp.spell,now->SongRank[j].spell);
				temp.score=now->SongRank[j].score;
				strcpy(now->SongRank[j].name,now->SongRank[i].name);
				strcpy(now->SongRank[j].singername,now->SongRank[i].singername);
				strcpy(now->SongRank[j].spell,now->SongRank[i].spell);
				now->SongRank[j].score=now->SongRank[i].score;
				strcpy(now->SongRank[i].name,temp.name);
				strcpy(now->SongRank[i].singername,temp.singername);
				strcpy(now->SongRank[i].spell,temp.spell);
				now->SongRank[i].score=temp.score;
			}
		}
	}
	printf("����ɹ�!��0������ҳ\n");
	int x;
	scanf("%d",&x);
	if(x==0)
	ShowAdmin(now);
}
void viewSongRank(Admin *now,int num,int page){
	getchar();
	int sum=num/10+1;
	system("cls");
	printf("���        ������         ������            ����\n");
	printf("--------------------------------------------------\n");
	if(page==sum){
		for(int i=0;i<num%10;i++){
			int k=(sum-1)*10+i;
			printf("%d\t        ��%s��\t         %s\t           %.2f\t",i+1,now->SongRank[k].name,now->SongRank[k].singername,now->SongRank[k].score);
			printf("\n");
		}
	}
	else{
		for(int i=0;i<10;i++){
			int k=(page-1)*10+i;
			printf("%d\t        ��%s��\t         %s\t           %.2f\t",i+1,now->SongRank[k].name,now->SongRank[k].singername,now->SongRank[k].score);
			printf("\n");
		}
	}
	printf("��%dҳ����%dҳ����һҳ��w��,��һҳ��s��,����ENTER������ҳ\n",page,sum);  
	char ch;
	ch=getchar();
		if(ch=='w'){
			if(page<=1){
				printf("��ǰ�Ѿ�����ҳ������������\n");
				viewSongRank(now,num,1);
			}
			else{
			  page=page-1;
			  viewSongRank(now,num,page);
			}
		}
		else if(ch=='s'){
			if(page==sum){
				printf("��ǰ�Ѿ������һҳ������������\n");
				viewSongRank(now,num,page);
			}
			else{
				page=page+1;
				viewSongRank(now,num,page);
			}
		}
		else if(ch=='\n'){
			ShowAdmin(now);
		}
}
void showChange(Admin *now){
	int count=0;
	char str[20];
	system("cls");
	printf("*********����ԱȨ��*********\n");
	printf("\n");
	printf("����ԱID��victor\n");
	printf("�����룺");
	getchar();
	int x=0;
	while(1){
		char ch=getch();
		if(ch!='\r'){
			str[x]=ch;
			x++;
			printf("*");
		}else break;
	}
	str[x]='\0';
	char key[20];
	getPassword(now,key);
	if(strcmp(str,key)==0){
		system("cls");
		printf("*********����ԱȨ��*********\n");
    	printf("\n");
    	printf("����ԱID��victor\n");
	    printf("�����������룺");
	    int y=0;
	    while(1){
	    	char ch=getch();
	    	if(ch!='\r'){
	    		str[y]=ch;
	    		y++;
	    		printf("*");
			}else break;
		}
		str[y]='\0';
		char newstr[20];
		printf("\n���ٴ�ȷ�����룺");
		int z=0;
		while(1){
			char ch=getch();
			if(ch!='\r'){
			   newstr[z]=ch;
			   z++;	
			   printf("*");
			}else break;
		}
		newstr[z]='\0';
		int newcount=0;
		while(newcount<3){
			if(strcmp(str,newstr)==0){
				newPassword(now,newstr);
				printf("\n�����޸ĳɹ�\n");
				printf("�����µ�½...\n");
				LoginAdmin(now,0); 
				break; 
			}
			newcount++;
			if(newcount==3){
				system("cls");
				printf("\n����������࣬�Զ�������һ����\n");
				ShowAdmin(now);
				break;
			}
			else{
			printf("\nǰ������������һ��\n");
			printf("��ENTER����������\n");
			getchar();
		    showChange(now);
			}
	}
}
            else {
            	printf("����������󣬰�0���³��ԣ���1����ԭ����\n");
            	int m;
            	scanf("%d",&m);
            	if(m==0)
            	showChange(now);
            	else if(m==1)
            	ShowAdmin(now);
			}
}
void newPassword(Admin *now,char key[20]){
	int i;
	for(i=0;i<20;i++){
		now->password[i]=key[i];
	}
}
void getPassword(Admin *now,char key[20]){
	int i;
	for(i=0;i<strlen(now->password);i++){
		key[i]=now->password[i];
	}
}
//������Admin����
void addBySinger(User *user){
	system("cls");
	printf("��������Ҫ���ҵĸ�������\n");
	char singer[100];
	scanf("%s",singer);
	getchar(); 
	FindSinger(&a,singer);	
} 
void FindSinger(Admin *now,char singer[100]){
	int i;
	int num[50];
	int count=0;
	int flag=0;
	for(i=0;i<song_numbers;i++){
		if(strcmp(singer,now->AllSongList[i].singername)==0){
			num[count]=now->AllSongList[i].num;
			count++;
			flag=1;
		}
	}
	if(flag==0) {
		printf("û�в��ҵ��ø�����ظ�������1����ԭ����...\n");
		int x;
		scanf("%d",&x);
		getchar();
		if(x==1){
		ShowUser();
	}
	}
	else
	forSelected(&user,now,1,num,count,1);
}
void addByName(User *user){
	system("cls");
	printf("��������Ҫ���ҵĸ�������\n");
	char name[100];
	scanf("%s",name);
	getchar();
	FindName(&a,name);
}
void FindName(Admin *now,char name[100]){
	int i;
	int num[50];
	int count=0;
	int flag=0;
	for(i=0;i<song_numbers;i++){
		if(strcmp(name,now->AllSongList[i].name)==0){
			num[count]=now->AllSongList[i].num;
			flag=1;
			count++;
		}
	}
	if(flag==0) {
		printf("û�в��ҵ��ø�������1����ԭ����...\n");
		int x;
		scanf("%d",&x);
		getchar();
		if(x==1){
		ShowUser();
	}
	}
	else
	forSelected(&user,now,1,num,count,2);
}
void addBySpell(User *user){
	system("cls");
	printf("��������Ҫ���ҵĸ���ƴ����\n");
	char spell[100];
	scanf("%s",spell);
	getchar(); 
	FindSpell(&a,spell);	
} 
void FindSpell(Admin *now,char spell[100]){
	int i;
	int num[50];
	int count=0;
	int flag=0;
	for(i=0;i<song_numbers;i++){
		if(strcmp(spell,now->AllSongList[i].spell)==0){
			num[count]=now->AllSongList[i].num;
			count++;
			flag=1;
		}
	}
	if(flag==0) {
		printf("û�в��ҵ���ظ�������1����ԭ����...\n");
		int x;
		scanf("%d",&x);
		getchar();
		if(x==1){
		ShowUser();
	}
	}
	else
	forSelected(&user,now,1,num,count,3);
}
void forSelected(User *user,Admin *now,int page,int num[50],int count,int flag){
	int all=count/10+1;
    system("cls");
	printf("���           ������           ������\n");
	printf("---------------------------------------\n");
	if(page==all){
		for(int i=0;i<count%10;i++){
			int k=(page-1)*10+i;
			printf("%d\t           ��%s��\t           %s\t",num[k],now->AllSongList[num[k]-1].name,now->AllSongList[num[k]-1].singername);
			printf("\n");
		}
	}
	else{
		for(int i=0;i<10;i++){
			int k=(page-1)*10+i;
			printf("%d\t           ��%s��\t           %s\t",num[k],now->AllSongList[num[k]-1].name,now->AllSongList[num[k]-1].singername);
			printf("\n");
		}
	}
	printf("��%dҳ����%dҳ����һҳ��w��,��һҳ��s��,���루p������ѡ�裬����ENTER������ҳ\n",page,all);
	char ch=getchar();
	getchar();
	if(ch=='\n')
	ShowUser();

	else if(ch=='w'){
			if(page<=1){
				printf("��ǰ�Ѿ�����ҳ������������\n");
				forSelected(user,now,1,num,count,flag);
			}
			else{
			  page=page-1;
			  forSelected(user,now,page,num,count,flag);
			}
		}
		else if(ch=='s'){
			if(page==all){
				printf("��ǰ�Ѿ������һҳ������������\n");
				forSelected(user,now,all,num,count,flag);
			}
			else{
				page=page+1;
				forSelected(user,now,page,num,count,flag);
			}
		} 
		else if(ch=='p'){
				printf("\n");
             	printf("��ѡ����Ҫ����赥�ĸ������\n");
             	int x;
             	scanf("%d",&x);
	            getchar();
                strcpy(user->WaitingList[order_songs].name,now->AllSongList[x-1].name);
                strcpy(user->WaitingList[order_songs].singername,now->AllSongList[x-1].singername);
                strcpy(user->WaitingList[order_songs].spell,now->AllSongList[x-1].spell);
             	order_songs++;	
             	printf("������ӳɹ�\n��1������ӣ���0����ԭ����\n");
             	int y;
             	scanf("%d",&y);
             	if(flag==1){
             	switch(y){
             		case 0:ShowUser();break;
             		case 1:addBySinger(user);break;
             		default:printf("���벻�Ϸ�\nϵͳ�Զ�����...\n");ShowUser();break;
				 }
		    	}
			    else if(flag==2){
			    switch(y){
             		case 0:ShowUser();break;
             		case 1:addByName(user);break;
             		default:printf("���벻�Ϸ�\nϵͳ�Զ�����...\n");ShowUser();break;
				 }	
				}
				else if(flag==3){
					switch(y){
             		case 0:ShowUser();break;
             		case 1:addBySpell(user);break;
             		default:printf("���벻�Ϸ�\nϵͳ�Զ�����...\n");ShowUser();break;
				 }
				}
		}

}
void viewSelected(User *user,int page,int flag){ //flag��������Ǵ�ʱ��ģ��Ϊ��һ�������ã��Ӷ�����ʾ�ù����ض��������� 
	getchar();
	int all=order_songs/10+1;
    system("cls");
    printf("               �ѵ����                 \n");
	printf("���            ������            ������\n");
	printf("----------------------------------------\n");
	if(page==all){
		for(int i=0;i<order_songs%10;i++){
			int k=(page-1)*10+i;
			printf("%d\t          ��%s��\t           %s\t",k+1,user->WaitingList[k].name,user->WaitingList[k].singername);
			printf("\n");
		}
	}
	else{
		for(int i=0;i<10;i++){
			int k=(page-1)*10+i;
			printf("%d\t          ��%s��\t           %s\t",k+1,user->WaitingList[k].name,user->WaitingList[k].singername);
			printf("\n");
		}
	}
	printf("��%dҳ����%dҳ����һҳ��w��,��һҳ��s��,����ENTER������ҳ",page,all);
	if(flag==0)//��ʱֻ�ǵ���Ϊ�˿��ѵ���� 
	printf("\n");
	else if(flag==1) //��ʱ��Ϊ���γ�ɾ������ҳ�� 
	printf(",����r����ɾ����������\n");
	else if(flag==2)//��ʱ��Ϊ���γ��ö�����ҳ�� 
	printf(",����t�����ö�����\n");
	else if(flag==3)//��ʱ��Ϊ���γɸ������۲���ҳ�� 
	printf(",����e���и������۲���\n");
	char ch=getchar();
	getchar();
	if(ch=='\n')
	ShowUser();
	else if(ch=='w'){
			if(page<=1){
				printf("��ǰ�Ѿ�����ҳ������������\n");
				viewSelected(user,1,flag);
			}
			else{
			  page=page-1;
			  viewSelected(user,page,flag);
		}
		}
		else if(ch=='s'){
			if(page==all){
				printf("��ǰ�Ѿ������һҳ������������\n");
				viewSelected(user,page,flag);
			}
			else{
				page=page+1;
				viewSelected(user,page,flag);
			}
		}
		else if(ch=='r'){
			removeSong(user);
		} 
		else if(ch=='t'){
			toTop(user);
		}
		else if(ch=='e'){
			evaluateSong(user,&a);
		}
}
void DeleteSong(User *user){
	system("cls");
	printf("��ǰ������:%s\n",user->WaitingList[0].name);
	printf("ȷ��Ҫɾ����y/n\n");
	char x;
	getchar();
	x=getchar();
	getchar();
	if(x=='y'){
		int i;
		for(i=1;i<order_songs;i++){
		strcpy(user->WaitingList[i-1].name,user->WaitingList[i].name);
		strcpy(user->WaitingList[i-1].singername,user->WaitingList[i].singername);
		strcpy(user->WaitingList[i-1].spell,user->WaitingList[i].spell);	
		user->WaitingList[i-1].score=user->WaitingList[i].score;
		user->WaitingList[i-1].sumAccess=user->WaitingList[i].sumAccess;
		}
		order_songs--;
		printf("�и�ɹ�����ǰ����Ϊ%s\n",user->WaitingList[0].name);
		printf("��1����ԭ����\n");
		int n;
		scanf("%d",&n);
		if(n==1)
		ShowUser();
	}
	else if(x=='n'){
		printf("ϵͳ�Զ�����ԭ����.....\n");
		ShowUser();
	}
}
void ForRemoveSong(User *user){
	viewSelected(user,1,1);
}
void removeSong(User *user){
	printf("��������Ҫɾ���ĸ������:\n"); 
	int x;
	scanf("%d",&x);
	order_songs;
	int i;
	for(i=x;i<order_songs;i++){
		strcpy(user->WaitingList[i-1].name,user->WaitingList[i].name);
		strcpy(user->WaitingList[i-1].singername,user->WaitingList[i].singername);
		strcpy(user->WaitingList[i-1].spell,user->WaitingList[i].spell);
		user->WaitingList[i-1].score=user->WaitingList[i].score;
		user->WaitingList[i-1].sumAccess=user->WaitingList[i].sumAccess;
	}
	order_songs--;
	printf("��0�鿴�ѵ��������1����ԭ����,��2����ɾ������\n");
	int y;
	scanf("%d",&y);
	if(y==0)
    viewSelected(user,1,0);
	else if(y==1)
	ShowUser();
	else if(y==2)
	ForRemoveSong(user); 
} 
void ForToTop(User *user){
	viewSelected(user,1,2);
} 
void toTop(User *user){
	printf("������Ҫ�ö��ĸ������\n");
	int x;
	scanf("%d",&x);
	char name[100];
	char singer[100];
	char spell[100];
	strcpy(name,user->WaitingList[x-1].name);
	strcpy(singer,user->WaitingList[x-1].singername);
	strcpy(spell,user->WaitingList[x-1].spell);	
	for(int i=x-2;i>=0;i--){
		strcpy(user->WaitingList[i+1].name,user->WaitingList[i].name);
		strcpy(user->WaitingList[i+1].singername,user->WaitingList[i].singername);
		strcpy(user->WaitingList[i+1].spell,user->WaitingList[i].spell);
    	user->WaitingList[i+1].score=user->WaitingList[i].score;
		user->WaitingList[i+1].sumAccess=user->WaitingList[i].sumAccess;
	}
	strcpy(user->WaitingList[0].name,name);
	strcpy(user->WaitingList[0].singername,singer);
	strcpy(user->WaitingList[0].spell,spell);
	printf("��0�鿴�ѵ��������1����ԭ����\n");
	int y;
	scanf("%d",&y);
	getchar();
	if(y==0)
	viewSelected(user,1,0);
	else if(y==1)
	ShowUser();
}
void ForEvaluateSong(User *user){
	viewSelected(user,1,3);
}
void evaluateSong(User *user,Admin *now){
	printf("������Ҫ���۵ĸ������\n");
	int x;
	scanf("%d",&x);
	char name[100];
	char singer[100];
	char spell[100];
	double score=0.0;
	strcpy(name,user->WaitingList[x-1].name);
	strcpy(singer,user->WaitingList[x-1].singername);
	strcpy(spell,user->WaitingList[x-1].spell);	
	int i;
	for(i=0;i<song_numbers;i++){
		if(strcmp(name,now->AllSongList[i].name)==0&&strcmp(singer,now->AllSongList[i].singername)==0){
			system("cls");
			printf("������0-5����\n");
			scanf("%lf",&score);
			now->AllSongList[i].state=1;
			now->AllSongList[i].score=(now->AllSongList[i].score*now->AllSongList[i].sumAccess+score)/(now->AllSongList[i].sumAccess+1);
			now->AllSongList[i].sumAccess+=1;
			break;
		}
	}
	printf("�������۳ɹ�����ǰ�ø�������Ϊ%.2f\n",now->AllSongList[i].score);
	printf("��0�������۸�������1����ԭ����\n");
	int y;
	scanf("%d",&y);
	if(y==0) 
	ForEvaluateSong(user);
	else if(y==1)
	ShowUser(); 
}
int main(){
	createSonglibrary(&a);
	showMain(); 
}
