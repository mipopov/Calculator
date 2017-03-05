#include<iostream>
#include<stack>
#include<string>
#include<cmath>

int stackoper(std::stack<int> &numberstack, std::stack<char> &symbolstack);
int prior(char c);
	
int main(){
	int pr = 0;
	std::string s, num = "";
	std::stack<char> symbolstack;
	std::stack<int> numberstack;
	std::cin >> s;
	for(int i = 0; i < s.size(); ++i){
		if(isdigit(s[i]))
			num += s[i];
		else{
			if(num.size() > 0){
				numberstack.push(stoi(num));
				num = "";	
			}
			if(s[i] == '('){
				symbolstack.push(s[i]);
				pr = 0;
			}	
			else
				if(s[i] == ')'){
					while (symbolstack.top() != '('){
						stackoper(numberstack,symbolstack);
						}
					symbolstack.pop();
					
					if (symbolstack.empty())
						pr = 0;
					else
						pr = prior(symbolstack.top());
				}
				else
					if (prior(s[i]) > pr){
						symbolstack.push(s[i]);
						pr = prior(symbolstack.top());
					}
					else{
						while (prior(symbolstack.top()) >= prior(s[i])){
							stackoper(numberstack,symbolstack);
							if (symbolstack.empty())
								break;
						}
					symbolstack.push(s[i]);
					} 	 
		}
		if (i == s.size() - 1){
			if (num.size() > 0)
                		numberstack.push(stoi(num));
			while (!symbolstack.empty())
				stackoper(numberstack,symbolstack);
		}
	}
	std::cout << numberstack.top() << std::endl;
	return 0;
}

int stackoper(std::stack<int> &numberstack, std::stack<char> &symbolstack){
	int a = numberstack.top();
        numberstack.pop();
        int b = numberstack.top();
        numberstack.pop();
        char c = symbolstack.top();
        symbolstack.pop();
        	switch (c){
                	case ('+') : { numberstack.push(a + b); break; }
                       	case ('-') : { numberstack.push(b - a); break; }
                     	case ('*') : { numberstack.push(a * b); break; }
                       	case ('/') : { numberstack.push(b / a); break; }
                        case ('^') : { numberstack.push(pow(b,a)); break; }
                       	case ('(') : { symbolstack.push('('); break; }
                       	default    : { return -1; }

		}
}	

int prior(char c){
	switch (c){
		case ('+') : { return 1; break; }
		case ('-') : { return 1; break; }
		case ('*') : { return 2; break; }
		case ('/') : { return 2; break; }
		case ('(') : { return 0; break; }
		case (')') : { return 5; break; }
		case ('^') : { return 4; break; }
		default: { std::cout << " Symbols arn't correct, try again" << std::endl; return -1; }
	}
} 
