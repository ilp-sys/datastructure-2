#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#define preset 999
using namespace std;

void setTree(vector<int> *tree){
    printf("트리 데이터 입력을 시작합니다.\n");

    int pos = -1;
    int data = preset;
    while(1){
        printf("pos, data = ? ");
        scanf("%d %d", &pos, &data);
        if(pos==0 && data==0) break;
        (*tree)[pos] = data;
    }

    printf("트리 데이터 입력이 완료되었습니다.\n");
}

void getTree(vector<int> tree, int height){

    int block = 2;
    int div = 2;
    int index = 1;
    int width = pow(2, height) + 1;
    for(int level = 1; level <= height; level++){
        printf("lev%d: ", level);
        block = block  + pow(2, level-1);
        div = div + pow(2, level-2);
        int bar_len = ceil((width - pow(2, level-1))/div);
        for(int it = 0; it < block; it++){
            if(level == 1){
                switch(it){
                    case 0: 
                        for(int i = 0; i < width/2; i++) printf(" ");
                        break;
                    case 1:
                        printf("%d", tree[index++]);
                        break;
                    case 2: 
                        for(int i = 0; i < width/2; i++) printf(" ");
                        break;
                }
            }
            else{ // level(2) ~ level(height)
                if(it%2 == 0 && it%4 ==0){
                    for(int i = 0; i < bar_len; i++)
                        printf(" ");
                }
                else if(it%2 == 0){
                    for(int i = 0; i < bar_len; i++)
                        printf("-");
                }
                else{//it%2 == 1
                    if(tree.at(index) == 999){
                        printf("*");
                        index++;
                        continue;
                    }
                    printf("%d", tree.at(index++));
                }
            }
        }
        printf("\n");
    }

    /*
    for(int i = 0; i < height; i++){
        printf("Lev%d:", i+1);
        for(int j = pow(2,i); j < pow(2, i+1); j++){
            printf("%4d", tree.at(j));
        }
        printf("\n");
    }
    */
}

void searchTree(vector<int> tree, int height){
    int data = preset;
    
    do{ 
      printf("정보를 알고 싶은 데이터를 입력하세요(종료 = 999):");
      scanf("%d", &data);

      if(data == 999) continue;
      auto it = find(tree.begin(), tree.end(), data);

      if(it == tree.end()){
          printf("%d: 노드가 존재하지 않습니다.\n", data);
          continue;
      }
      
      int index = distance(tree.begin(), it);

      int parent = index%2 == 0 ? index/2 : (index-1)/2;
      int left_child = (index*2) > (tree.size()-1) ? 0: index*2;
      int right_child = (index*2+1) > (tree.size()-1) ? 0:(index*2+1);

      vector<int> sibling;
      int level = log2(index) + 1;
      for(int i = pow(2,level-1); i <= pow(2, level) -1; i++){
          if(i == index)
             continue;
          sibling.push_back(i);
      }

      //자식 노드들의 인덱스가 벡터의 크기를 넘어가는 경우 0으로 저장
      //노드는 1번 인덱스부터 시작, 인덱스가 0이면 "none" 출력
      //0번 인덱스에는 preset으로 999가 저장되어 있음

      vector<int> print_list = {parent, left_child, right_child};
      string text[3] = {"부모= ", ", 왼쪽자식= ", ", 오른쪽자식= "};

      
      printf("%d: ", data);
      for(int i = 0; i < 3; i++){
          if(tree.at(print_list[i]) == 999)
              printf("%s %s", text[i].c_str(), "none");
          else
              printf("%s %d", text[i].c_str(), tree.at(print_list[i]));
      }

      printf(", 형제노드 = ");
      if(sibling.size() == 0)
          printf("none");
      else
          for(int i = 0; i < sibling.size(); i++){
              if(tree.at(sibling.at(i)) == 999)
                  continue;
              else
                  printf("%d ", tree.at(sibling.at(i)));
          }

      printf("\n");
    }while(data != 999);
}

int main(int argc, char* argv[]){
	
	//트리 크기 입력받기
	int height = 0;
	printf("tree height? ");
	scanf("%d", &height);

	//벡터 선언& 초기화
	vector<int> tree(pow(2,height), preset);

	//트리 정보 입력
	setTree(&tree);

	//트리 정보 출력
	getTree(tree, height);
	
	//트리 정보 검색
	searchTree(tree, height);

	printf("종료합니다.\n");
	return 0;
}
