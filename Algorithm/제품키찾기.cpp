/*
제품키 찾기
시간 제한: 1 Sec  메모리 제한: 128 MB
[제출]
문제 설명

 어떤 제품의 제품키는 다음과 같은 규칙을 갖는다.
--------------------------------------------------------------------------------------------------------------
 <규칙 설명>
 제품키는 다음과 같이 5문자씩 5묶음으로 총 25문자이다. ( 한 묶음에 다섯 문자 )
□□□□■ - □□□□■ - □□□□■ - □□□□■ - □□□□■
 제품키의 각 문자는 숫자와 알파벳 대문자, 즉 0~9, A~Z 로만 이루어져있다.
 각 묶음의 검은 부분은 제품키를 검증하기 위한 검증문자로서 다른 문자들의 관계로 나타난다.
 검증문자 앞에 있는 다섯 개의 문자 (첫번째 검증문자의 경우 앞에 네 개의 문자 밖에 없는데 
가장 앞에 0 이 있다고 가정한다. 
나머지 검증문자들의 경우 이전 검증문자까지 포함하여 다섯 개의 문자) 에 대한 식으로 나타낼 수 있다.
 검증문자 = ( ① * 2 + ② * 3 + ③ * 5 + ④ * 7 + ⑤ * 11 ) % 36
 ( 문자 0~9 는 숫자 0~9 로 변환하고, 문자 A~Z 는 숫자 10~35 로 변환하여 위 식에 적용 )
--------------------------------------------------------------------------------------------------------------
 이와 같은 제품키들이 주어진 문자열에 숨겨져 있다.
 위의 규칙을 만족하는 제품키들을 모두 찾아 출력하자.
 
입력
입력되는 문자열은 한 줄이다.
제품키의 5묶음을 구분하기 위한 ‘-‘ 같은 문자 없이, 묶음끼리 붙어있을 수 있다.
주어진 문자열에는 제품키를 구성하는 문자( 0~9, A~Z )가 아닌 문자도 포함되어있다. 
이러한 문자들은 제품키의 묶음 사이에만 있을 수 있고, 2개 이상 있을 수 있다. 
한 묶음 안에는 이런 문자가 있을 수 없다.
제품키끼리는 겹쳐져 있지 않다.
abcdef-ghijk 경우 bcdef 와 ghjik 만 제품키에 포함 될 수 있습니다.( 검증문자는 차후 문제)
abcdefghijk 경우 abcde가 검증문자에 맞지 않는 경우 bcdef를 가지고 
시작 하되 마지막 제품키에서 검증문자가 맞지 않는다면 
다시 cdefg를 가지고 시작 해야 합니다.
(참고, 입력 예시로 주어진 문자열은 여러줄처럼 보이지만 실제로는 한줄이다.)
출력
문자열에서 제품키를 찾은 순서대로 각 줄에 출력한다.

입력 예시
1BHD'3+24/9DQM4SCIJBJ5C8VXH93D0NL(%^SGYYR*@WPL"{E0Y30AGDFYG\|SZ92G*BLN2TEM09L:DNN9P$M8&NWG9QRPU516CQ7-+G7XHB">A1PIY/7Y2YZ-RIVSBTRMPFH&L-4\71K2L01^35EDP\|{GWMHN;=?G80SA(ROPIJBEJ5(28DCOF3;ZNS53[4Q8PB&DISKR>IG9FKFBLQY6FX2FY4IPHW=6I5KV.)N4KJW,B8PCC\<3W1TFC7CITEM80EXUJOQ>(TVTNUU4BPIQFZSM,S3N7L.'4K6LV8XDHP#"CFSVEISAW4~#G77B9MYFWR;%/HWMZCH3UG88GHO&%(WRPA$RZGG4++EFQWB5ZJKP_H8LH7]'\VX7K28Z9I\H7&2C45JMQXS){UEL6X!3LSRPPJ6VR>JMOAWAKAZLN29Z:_2O86SU\JNBUR$/*UYR9Q=#?STKS9WKU14D9QFJ160OA8,^~VQCWRJ6ZO2'BSZI8"NYBG4J](VWEZEF0Q_D2PN9\ .HSTKK&M4CCI%@YN58G=_\2AGI3;^WR%G< |1LMXHBXCUCU1Z< XXHI3%[^IWQ5P\=6N93S9L5IFB1FILKKPQ8EJ@FQQE9_@8Z2C3}P8TOC OT1H4V3@ZGYWQ(TTS7XCTD~/_ULJB7]|POEET{INPIO/SRLGF7YTG5XSPKRY">4HKER" WRMLM{TSR5BSFNJBO#J6R2{GAYPPE2GB^@^AGGO4:>,2B18K($CWXQXSBT7I)S3KX9Z74LIDTCJ9-_3L6FF{/XPYME!#3ISSJ?"7F59H7XA!W?OP68X0O9ED=+LF3IN3OMX8VEHCYB2BCXT[}2\%40'MEG6S7R  :K0DFA84YOQ>;I95WY8ZFKH BQSH72N4M*YIAG6;;I4TRA-"B4FSI+)YA42M]CZBG52I3K49Z22OX;SDIVY( 0USGE?9LR10RHICSA(G9'TPW5FFK8ERWN#NLN54[*-W17GA'7ILPDVGC3TX"44N'V4ERSY9MCK9VD7IR{OA897W93R5[}53YPEHU07O74UZ0ZXAMOI2"DLJR2(;+CJYZ2A38CL $>9N9CKEKDFICK0L%^SK477Q% VNFD4%0XRIKPTCMA_>T961QYT=]PD?4534XRXXG5^|}ELL5Z-K4VJ0]TDER7&THD86IQZMMARNT2P$5BUIO=@(V4AIX+7SNAUY1RJP

출력 예시
4IPHW-6I5KV-N4KJW-B8PCC-3W1TF
C7CIT-EM80E-XUJOQ-TVTNU-U4BPI
QFZSM-S3N7L-4K6LV-8XDHP-CFSVE
ISAW4-G77B9-MYFWR-HWMZC-H3UG8
60OA8-VQCWR-J6ZO2-BSZI8-NYBG4
SPKRY-4HKER-WRMLM-TSR5B-SFNJB
Z22OX-SDIVY-0USGE-9LR10-RHICS
RNT2P-5BUIO-V4AIX-7SNAU-Y1RJP

*/

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

/*
1BHD'3+24/9DQM4SCIJBJ5C8VXH93D0NL(%^SGYYR*@WPL"{E0Y30AGDFYG\|SZ92G*BLN2TEM09L:DNN9P$M8&NWG9QRPU516CQ7-+G7XHB">A1PIY/7Y2YZ-RIVSBTRMPFH&L-4\71K2L01^35EDP\|{GWMHN;=?G80SA(ROPIJBEJ5(28DCOF3;ZNS53[4Q8PB&DISKR>IG9FKFBLQY6FX2FY4IPHW=6I5KV.)N4KJW,B8PCC\<3W1TFC7CITEM80EXUJOQ>(TVTNUU4BPIQFZSM,S3N7L.'4K6LV8XDHP#"CFSVEISAW4~#G77B9MYFWR;%/HWMZCH3UG88GHO&%(WRPA$RZGG4++EFQWB5ZJKP_H8LH7]'\VX7K28Z9I\H7&2C45JMQXS){UEL6X!3LSRPPJ6VR>JMOAWAKAZLN29Z:_2O86SU\JNBUR$/*UYR9Q=#?STKS9WKU14D9QFJ160OA8,^~VQCWRJ6ZO2'BSZI8"NYBG4J](VWEZEF0Q_D2PN9\ .HSTKK&M4CCI%@YN58G=_\2AGI3;^WR%G< |1LMXHBXCUCU1Z< XXHI3%[^IWQ5P\=6N93S9L5IFB1FILKKPQ8EJ@FQQE9_@8Z2C3}P8TOC OT1H4V3@ZGYWQ(TTS7XCTD~/_ULJB7]|POEET{INPIO/SRLGF7YTG5XSPKRY">4HKER" WRMLM{TSR5BSFNJBO#J6R2{GAYPPE2GB^@^AGGO4:>,2B18K($CWXQXSBT7I)S3KX9Z74LIDTCJ9-_3L6FF{/XPYME!#3ISSJ?"7F59H7XA!W?OP68X0O9ED=+LF3IN3OMX8VEHCYB2BCXT[}2\%40'MEG6S7R  :K0DFA84YOQ>;I95WY8ZFKH BQSH72N4M*YIAG6;;I4TRA-"B4FSI+)YA42M]CZBG52I3K49Z22OX;SDIVY( 0USGE?9LR10RHICSA(G9'TPW5FFK8ERWN#NLN54[*-W17GA'7ILPDVGC3TX"44N'V4ERSY9MCK9VD7IR{OA897W93R5[}53YPEHU07O74UZ0ZXAMOI2"DLJR2(;+CJYZ2A38CL $>9N9CKEKDFICK0L%^SK477Q% VNFD4%0XRIKPTCMA_>T961QYT=]PD?4534XRXXG5^|}ELL5Z-K4VJ0]TDER7&THD86IQZMMARNT2P$5BUIO=@(V4AIX+7SNAUY1RJP
*/

string fileRead(){
	string line[25];
	string str="";
	ifstream inFile;
	inFile.open("KeyList.txt");
	for(int i=0;i<25;++i){
		inFile>>line[i];
		str+=line[i];
	}
	inFile.close();
	return str;
}

int transCharToInt(char ch){
	if(ch>='0' && ch<='9') return ch-'0';
	return ch-'A'+10;
}

bool charCheck(char ch){
	if((ch>='A' && ch<='Z')||(ch>='0' && ch<='9')) return true;
	else return false;
}
bool calc(vector<char> &calcList,char *tmp,bool &first){
	if(first){
		first=false;
		return ((transCharToInt(tmp[0])*3
				+transCharToInt(tmp[1])*5
				+transCharToInt(tmp[2])*7
				+transCharToInt(tmp[3])*11)
				%36)==transCharToInt(tmp[4]);
	}
	else{
		return ((transCharToInt(calcList.back())*2
				+transCharToInt(tmp[0])*3
				+transCharToInt(tmp[1])*5
				+transCharToInt(tmp[2])*7
				+transCharToInt(tmp[3])*11)
				%36)==transCharToInt(tmp[4]);
	}
}

bool setCheck(string&keyList,char*tmp,int idx){
	
	for(int i=0;i<5;++i){
		if(charCheck(keyList[idx+i])) tmp[i]=keyList[idx+i];
		else{
			return false;
		}
	}
	return true;
}

void solv(){
	string keyList=fileRead();
	const int size=keyList.size();
	bool first=true;
	int cnt=0;
	char tmp[5];
	int otherChar=0;
	vector<char> calcList;
	vector<char> key;

	for(int i=0;i<size;++i){ // 전체 반복
		
		if(setCheck(keyList,tmp,i)){ // 첫 스타트
			
			if(calc(calcList,tmp,first)){ // 첫 5개가 공식에 맞음 다음 20개들을 찾아야함.
				
				int nextIdx=i+5;
				
				for(int j=0;j<5;++j) calcList.push_back(tmp[j]);
				++cnt; // 묶음 수 확인

				for(int idx=nextIdx;idx<size;++idx){
					if(charCheck(keyList[idx])){
						if(setCheck(keyList,tmp,idx)){
							if(otherChar!=idx-nextIdx && otherChar){	// 묶음 중간에 문자+특수문자가 포함됨.
																		// 참 경우가 다양함.
																		// 문자1 !#$ 문자2
																		// 문자1 !@#문자!# 문자2
																		// 문자1 문자 문자2
																		// 다 생각해서 해줘야함...
																		// 문자1의 끝 인덱스와 문자2의 첫 인덱스
																		// 사이의 차 값을 이용해서 해결..
																		// 문자1 문자2 사이의 특수문자들의 갯수를 세어서
																		// 문자2 첫번째 인덱스와 문자1 끝+1 인덱스 차이의 값과 비교..
								cnt=0;
								break;
							}
							else{
								if(calc(calcList,tmp,first)){
									for(int j=0;j<5;++j) calcList.push_back(tmp[j]);
									nextIdx=idx+5;
									otherChar=0;
									if(++cnt==5) break;
								}
								else{
									continue;
								}
								
							}
						}
						else continue;
					}
					else ++otherChar;
				}

				if(cnt>=4){
					for(vector<char>::const_iterator iter=calcList.begin();iter!=calcList.end();++iter){
						key.push_back(*iter);
					}
				}
				otherChar=0;
				cnt=0;
				first=true;
				calcList.erase(calcList.begin(),calcList.end());
			}
			else{
				cnt=0;
				first=true;
			}
		}
	}

	for(int i=1;i<=key.size();++i){
		cout<<key[i-1];
		if(i%5==0){
			if(i%25==0) cout<<endl;
			else cout<<"-";
		}
	}
}

int main(){
	solv();
	return 0;
}
