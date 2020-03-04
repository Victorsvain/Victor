#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h> 
int song_numbers;//歌曲库中歌曲数
int order_songs=0;//用户点歌数 
struct song{
	int num;
	char name[100];
	char singername[100];
	char spell[100];
	double score;
	int sumAccess;
	int state;   //1代表被评价，0代表未被评价 
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
//以上为Admin函数
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
	printf("      KTV点歌系统       \n");
	printf("===========================\n");
	printf("*      1 用户直达        *\n");
	printf("*      2 管理员登陆      *\n");
	printf("*      3 退出系统        *\n"); 
	printf("===========================\n");
	printf("请输入选项【】\n");
	int x;
	scanf("%d",&x);
	switch(x){
		case 1:ShowUser(); break;
		case 2:LoginAdmin(&a,0);break;
		case 3:ShowEnd();break;
		default:printf("\n输入不合法\n");
		        printf("按ENTER键重新输入...\n");
		        getchar();
		        showMain(); 
	} 
} 
void ShowEnd(){
	system("cls");
	printf("感谢您的光临，欢迎下次再来！\n");
	printf("      系统正在退出.........\n");
}
void LoginAdmin(Admin *now,int count){
	getchar();
	system("cls");
    printf("**********管理员登陆*************\n");
    printf("管理员ID：victor\n");
	printf("密码：\n");
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
		printf("登陆成功，系统正在自动跳转......\n");
		ShowAdmin(now);
	}
	else{
		count++;
		if(count==3){
			system("cls");
			printf("密码错误次数过多，系统自动返回.....\n");
			showMain(); 
		}
		else{
			system("cls");
			printf("\n密码输入错误%d次，还有%d次输入机会\n",count,3-count);
			LoginAdmin(now,count);
		}
	}
}
	
void ShowAdmin(Admin *now){
	system("cls");
	printf("      KTV管理员系统       \n");
	printf("===========================\n");
	printf("*      1 所有歌曲        *\n");
	printf("*      2 添加歌曲        *\n");
	printf("*      3 批量导入歌曲    *\n");
	printf("*      4 歌曲排序        *\n");
	printf("*      5 查看歌曲排名    *\n"); 
	printf("*      6 修改密码        *\n");
	printf("*      0 退    出        *\n");
	printf("请输入选项【】\n");	
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
		default:printf("\n输入不合法\n");
		        printf("按ENTER键重新输入...\n");
		        getchar();
		        ShowAdmin(now);
	}
}
void ShowUser(){
	system("cls");
	printf("      KTV用户系统       \n");
	printf("===========================\n");
	printf("*      1 歌手点歌        *\n");
	printf("*      2 歌名点歌        *\n");
	printf("*      3 拼音点歌        *\n");
	printf("*      4 所有歌曲        *\n");
	printf("*      5 已点歌曲        *\n");
	printf("*      6 切    歌        *\n"); 
	printf("*      7 删除歌曲        *\n");
	printf("*      8 置顶歌曲        *\n");
	printf("*      9 歌曲评分        *\n");
	printf("*      0 退    出        *\n");
	printf("请输入选项【】\n");	
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
		default:printf("\n输入不合法\n");
		        printf("按ENTER键重新输入...\n");
		        getchar();
		        ShowUser();
		
	}
}
void viewAllsongs(Admin *now,int num,int page,int judge){
	getchar();
	int sum=num/10+1;
	system("cls");
	printf("编号\t             歌曲名\t              歌手名\t\n");
	printf("-------------------------------------------------\n");
	if(page==sum){
		for(int i=0;i<num%10;i++){
			int k=(sum-1)*10+i;
			printf("%d\t        《%s》\t         %s\t",i+1,now->AllSongList[k].name,now->AllSongList[k].singername);
			printf("\n");
		}
	}
	else{
		for(int i=0;i<10;i++){
			int k=(page-1)*10+i;
			printf("%d\t        《%s》\t         %s\t",i+1,now->AllSongList[k].name,now->AllSongList[k].singername);
			printf("\n");
		}
	}
	printf("第%d页，共%d页，上一页（w）,下一页（s）,输入ENTER返回主页\n",page,sum);  
	char ch;
	ch=getchar();
		if(ch=='w'){
			if(page<=1){
				printf("当前已经是首页，请重新输入\n");
				viewAllsongs(now,num,1,judge);
			}
			else{
			  page=page-1;
			  viewAllsongs(now,num,page,judge);
			}
		}
		else if(ch=='s'){
			if(page==sum){
				printf("当前已经是最后一页，请重新输入\n");
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
	printf("请输入："); 
	printf("歌名\t\t歌手\t\t拼音\n");
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
    	printf("该歌曲已经存在\n");
    	printf("添加失败\n");
    	printf("按0返回原界面，按1重新添加歌曲\n");
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
      printf("歌曲添加成功！\n");
      printf("按0返回原界面，按1继续添加歌曲\n");
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
	printf("请选择要导入的歌单\n");
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
	printf("歌曲添加成功！\n");
	printf("按0返回上一界面,按1退出系统\n");
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
	printf("排序成功!按0返回主页\n");
	int x;
	scanf("%d",&x);
	if(x==0)
	ShowAdmin(now);
}
void viewSongRank(Admin *now,int num,int page){
	getchar();
	int sum=num/10+1;
	system("cls");
	printf("编号        歌曲名         歌手名            评分\n");
	printf("--------------------------------------------------\n");
	if(page==sum){
		for(int i=0;i<num%10;i++){
			int k=(sum-1)*10+i;
			printf("%d\t        《%s》\t         %s\t           %.2f\t",i+1,now->SongRank[k].name,now->SongRank[k].singername,now->SongRank[k].score);
			printf("\n");
		}
	}
	else{
		for(int i=0;i<10;i++){
			int k=(page-1)*10+i;
			printf("%d\t        《%s》\t         %s\t           %.2f\t",i+1,now->SongRank[k].name,now->SongRank[k].singername,now->SongRank[k].score);
			printf("\n");
		}
	}
	printf("第%d页，共%d页，上一页（w）,下一页（s）,输入ENTER返回主页\n",page,sum);  
	char ch;
	ch=getchar();
		if(ch=='w'){
			if(page<=1){
				printf("当前已经是首页，请重新输入\n");
				viewSongRank(now,num,1);
			}
			else{
			  page=page-1;
			  viewSongRank(now,num,page);
			}
		}
		else if(ch=='s'){
			if(page==sum){
				printf("当前已经是最后一页，请重新输入\n");
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
	printf("*********管理员权限*********\n");
	printf("\n");
	printf("管理员ID：victor\n");
	printf("旧密码：");
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
		printf("*********管理员权限*********\n");
    	printf("\n");
    	printf("管理员ID：victor\n");
	    printf("请输入新密码：");
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
		printf("\n请再次确认密码：");
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
				printf("\n密码修改成功\n");
				printf("请重新登陆...\n");
				LoginAdmin(now,0); 
				break; 
			}
			newcount++;
			if(newcount==3){
				system("cls");
				printf("\n输入次数过多，自动返回上一界面\n");
				ShowAdmin(now);
				break;
			}
			else{
			printf("\n前后密码需输入一致\n");
			printf("按ENTER键重新输入\n");
			getchar();
		    showChange(now);
			}
	}
}
            else {
            	printf("密码输入错误，按0重新尝试，按1返回原界面\n");
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
//以上是Admin部分
void addBySinger(User *user){
	system("cls");
	printf("请输入需要查找的歌手名：\n");
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
		printf("没有查找到该歌手相关歌曲，按1返回原界面...\n");
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
	printf("请输入需要查找的歌曲名：\n");
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
		printf("没有查找到该歌曲，按1返回原界面...\n");
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
	printf("请输入需要查找的歌曲拼音：\n");
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
		printf("没有查找到相关歌曲，按1返回原界面...\n");
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
	printf("编号           歌曲名           歌手名\n");
	printf("---------------------------------------\n");
	if(page==all){
		for(int i=0;i<count%10;i++){
			int k=(page-1)*10+i;
			printf("%d\t           《%s》\t           %s\t",num[k],now->AllSongList[num[k]-1].name,now->AllSongList[num[k]-1].singername);
			printf("\n");
		}
	}
	else{
		for(int i=0;i<10;i++){
			int k=(page-1)*10+i;
			printf("%d\t           《%s》\t           %s\t",num[k],now->AllSongList[num[k]-1].name,now->AllSongList[num[k]-1].singername);
			printf("\n");
		}
	}
	printf("第%d页，共%d页，上一页（w）,下一页（s）,输入（p）进行选歌，输入ENTER返回主页\n",page,all);
	char ch=getchar();
	getchar();
	if(ch=='\n')
	ShowUser();

	else if(ch=='w'){
			if(page<=1){
				printf("当前已经是首页，请重新输入\n");
				forSelected(user,now,1,num,count,flag);
			}
			else{
			  page=page-1;
			  forSelected(user,now,page,num,count,flag);
			}
		}
		else if(ch=='s'){
			if(page==all){
				printf("当前已经是最后一页，请重新输入\n");
				forSelected(user,now,all,num,count,flag);
			}
			else{
				page=page+1;
				forSelected(user,now,page,num,count,flag);
			}
		} 
		else if(ch=='p'){
				printf("\n");
             	printf("请选择需要加入歌单的歌曲编号\n");
             	int x;
             	scanf("%d",&x);
	            getchar();
                strcpy(user->WaitingList[order_songs].name,now->AllSongList[x-1].name);
                strcpy(user->WaitingList[order_songs].singername,now->AllSongList[x-1].singername);
                strcpy(user->WaitingList[order_songs].spell,now->AllSongList[x-1].spell);
             	order_songs++;	
             	printf("歌曲添加成功\n按1继续添加，按0返回原界面\n");
             	int y;
             	scanf("%d",&y);
             	if(flag==1){
             	switch(y){
             		case 0:ShowUser();break;
             		case 1:addBySinger(user);break;
             		default:printf("输入不合法\n系统自动返回...\n");ShowUser();break;
				 }
		    	}
			    else if(flag==2){
			    switch(y){
             		case 0:ShowUser();break;
             		case 1:addByName(user);break;
             		default:printf("输入不合法\n系统自动返回...\n");ShowUser();break;
				 }	
				}
				else if(flag==3){
					switch(y){
             		case 0:ShowUser();break;
             		case 1:addBySpell(user);break;
             		default:printf("输入不合法\n系统自动返回...\n");ShowUser();break;
				 }
				}
		}

}
void viewSelected(User *user,int page,int flag){ //flag是用作标记此时该模块为哪一功能所用，从而来显示该功能特定需求内容 
	getchar();
	int all=order_songs/10+1;
    system("cls");
    printf("               已点歌曲                 \n");
	printf("编号            歌曲名            歌手名\n");
	printf("----------------------------------------\n");
	if(page==all){
		for(int i=0;i<order_songs%10;i++){
			int k=(page-1)*10+i;
			printf("%d\t          《%s》\t           %s\t",k+1,user->WaitingList[k].name,user->WaitingList[k].singername);
			printf("\n");
		}
	}
	else{
		for(int i=0;i<10;i++){
			int k=(page-1)*10+i;
			printf("%d\t          《%s》\t           %s\t",k+1,user->WaitingList[k].name,user->WaitingList[k].singername);
			printf("\n");
		}
	}
	printf("第%d页，共%d页，上一页（w）,下一页（s）,输入ENTER返回主页",page,all);
	if(flag==0)//此时只是单纯为了看已点歌曲 
	printf("\n");
	else if(flag==1) //此时是为了形成删除操作页面 
	printf(",输入r进行删除歌曲操作\n");
	else if(flag==2)//此时是为了形成置顶操作页面 
	printf(",输入t进行置顶操作\n");
	else if(flag==3)//此时是为了形成歌曲评价操作页面 
	printf(",输入e进行歌曲评价操作\n");
	char ch=getchar();
	getchar();
	if(ch=='\n')
	ShowUser();
	else if(ch=='w'){
			if(page<=1){
				printf("当前已经是首页，请重新输入\n");
				viewSelected(user,1,flag);
			}
			else{
			  page=page-1;
			  viewSelected(user,page,flag);
		}
		}
		else if(ch=='s'){
			if(page==all){
				printf("当前已经是最后一页，请重新输入\n");
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
	printf("当前歌曲是:%s\n",user->WaitingList[0].name);
	printf("确认要删除吗？y/n\n");
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
		printf("切歌成功，当前歌曲为%s\n",user->WaitingList[0].name);
		printf("按1返回原界面\n");
		int n;
		scanf("%d",&n);
		if(n==1)
		ShowUser();
	}
	else if(x=='n'){
		printf("系统自动返回原界面.....\n");
		ShowUser();
	}
}
void ForRemoveSong(User *user){
	viewSelected(user,1,1);
}
void removeSong(User *user){
	printf("请输入想要删除的歌曲编号:\n"); 
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
	printf("按0查看已点歌曲，按1返回原界面,按2继续删除歌曲\n");
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
	printf("请输入要置顶的歌曲编号\n");
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
	printf("按0查看已点歌曲，按1返回原界面\n");
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
	printf("请输入要评价的歌曲编号\n");
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
			printf("请输入0-5评分\n");
			scanf("%lf",&score);
			now->AllSongList[i].state=1;
			now->AllSongList[i].score=(now->AllSongList[i].score*now->AllSongList[i].sumAccess+score)/(now->AllSongList[i].sumAccess+1);
			now->AllSongList[i].sumAccess+=1;
			break;
		}
	}
	printf("歌曲评价成功，当前该歌曲评分为%.2f\n",now->AllSongList[i].score);
	printf("按0继续评价歌曲，按1返回原界面\n");
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
