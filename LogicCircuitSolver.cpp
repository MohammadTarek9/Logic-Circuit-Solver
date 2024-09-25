#include <iostream>
#include<string>
#include<cctype>
using namespace std;
int count(string x, char a)
{
    int res = 0;
    for (int i = 0; i < x.length(); i++)
    {
        if (x[i] == a)
        {
            res++;
        }
    }
    return res;
}
int logicalop(string operation, string firstop, string secondop)
{
    int res = 0;
    if (operation == "AND")
    {
        //cout<<firstop<<endl;
        //cout<<secondop<<endl;

        res = stoi(firstop) & stoi(secondop);
    }
    else if (operation == "OR")
    {
        res = stoi(firstop) | stoi(secondop);
    }
    else if (operation == "NAND")
    {
        res = !(stoi(firstop) & stoi(secondop));
    }
    else if (operation == "NOR")
    {
        res = !(stoi(firstop) | stoi(secondop));
    }
    else if (operation == "XOR")
    {
        res = stoi(firstop) ^ stoi(secondop);
    }
    else
    {
        cout << "Wrong Logic Circuit Description" << endl;
        exit(0);
    }

    return res;
}
int numberoflogicalgates(string x, string logicalop)
{
    int count = 0;
    int pos = x.find(logicalop);
    while (pos < x.length())
    {

        if (pos == 0 || x.at(pos - 1) == ' ')
            count++;
        pos = pos + logicalop.length();
        pos = x.find(logicalop, pos);
    }
    return count;

}
int findNthOccur(string str,
    char ch, int N)
{
    int occur = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ch) {
            occur += 1;
        }
        if (occur == N)
            return i;
    }
    return -1;
}
string output(string x, int numberofop)
{
    string resstr = "";
    if (numberofop == 1)
    {
        string parentoperator = x.substr(0, x.find(' '));
        if (parentoperator == "NOT")
        {
            //cout << x.find('e') << endl;
            string firstoperand = x.substr(parentoperator.length() + 1, 1);
            //cout << firstoperand << endl;
            if (firstoperand != "0" && firstoperand != "1")
            {
                cout << "result : BAD input : missing input number" << endl;
                exit(0);
            }
            int res = !stoi(firstoperand);
            resstr = to_string(res);
        }
        else
        {
            //cout << x << endl;
            //cout << parentoperator << endl;
            if (parentoperator != "AND" && parentoperator != "OR" && parentoperator != "NAND" && parentoperator != "NOR" && parentoperator != "XOR")
            {
                cout << "Wrong Logic Circuit Description" << endl;
                exit(0);
            }
            else
            {
                string firstoperand = x.substr(parentoperator.length() + 1, 1);
                if (firstoperand != "0" && firstoperand != "1")
                {
                    cout << "result : BAD input : missing input number" << endl;
                    exit(0);
                }
                //cout << firstoperand << endl;
                //cout << x.find('e')-7 << endl;
                string secondoperand = x.substr(parentoperator.length() + 3, 1);
                if (secondoperand != "0" && secondoperand != "1")
                {
                    cout << "result : BAD input : missing input number" << endl;
                    exit(0);
                }

                //cout << secondoperand << endl;

                int res = logicalop(parentoperator, firstoperand, secondoperand);

                resstr = to_string(res);
            }

        }
    }

    else
    {
        //cout << x << endl;
        string parentoperator = x.substr(0, x.find(' '));
        //cout << parentoperator << endl;
        string operation = "";

        if (x.at(x.find(' ') + 1) == '0' || x.at(x.find(' ') + 1) == '1')
        {

            operation = x.substr(parentoperator.length() + 3, ((x.find('e')) - (x.find(' ') + 3) + 1));
            //cout<<operation<<endl;
            int countchildoperations = 0;
            string childopres = "";
            int numand = numberoflogicalgates(operation, "AND");
            countchildoperations += numand;
            numand = numberoflogicalgates(operation, "OR");
            countchildoperations += numand;
            numand = numberoflogicalgates(operation, "NOT");
            countchildoperations += numand;
            numand = numberoflogicalgates(operation, "XOR");
            countchildoperations += numand;
            numand = numberoflogicalgates(operation, "NAND");
            countchildoperations += numand;
            numand = numberoflogicalgates(operation, "NOR");
            countchildoperations += numand;
            if (countchildoperations > 1)
            {
                int nthe = findNthOccur(x, 'e', countchildoperations);

                operation = x.substr(parentoperator.length() + 3, (nthe - (x.find(' ') + 3) + 1));

                int numand = numberoflogicalgates(operation, "AND");
                countchildoperations = 0;
                countchildoperations += numand;
                numand = numberoflogicalgates(operation, "OR");
                countchildoperations += numand;
                numand = numberoflogicalgates(operation, "NOT");
                countchildoperations += numand;
                numand = numberoflogicalgates(operation, "XOR");
                countchildoperations += numand;
                numand = numberoflogicalgates(operation, "NAND");
                countchildoperations += numand;
                numand = numberoflogicalgates(operation, "NOR");
                countchildoperations += numand;
                nthe = findNthOccur(x, 'e', countchildoperations);
                operation = x.substr(parentoperator.length() + 3, (nthe - (x.find(' ') + 3) + 1));
                //cout<<operation<<endl;
                childopres = output(operation, count(operation, 'e'));
                x.replace(x.find(' ') + 3, (nthe - (x.find(' ') + 3) + 1), childopres + " ");
                //cout<<x<<endl;
                resstr = output(x, count(x, 'e'));
            }
            else {


                string childoperation = operation.substr(0, operation.find(' '));
                //cout << childoperation << endl;
                if (childoperation == "NOT")
                {
                    string firstoperand = operation.substr(childoperation.length() + 1, 1);
                    // cout << firstoperand << endl;
                    if (firstoperand != "0" && firstoperand != "1")
                    {
                        cout << "result : BAD input : missing input number" << endl;
                        exit(0);

                    }
                    int res = !stoi(firstoperand);
                    string tempresstr = to_string(res);
                    //cout << x.find(' ') + 3 << endl;
                    //cout << (x.find('e')) - (x.find(' ') + 3) + 1 << endl;
                    x.replace(x.find(' ') + 3, ((x.find('e')) - (x.find(' ') + 3) + 1), tempresstr);
                    //cout << x << endl;
                    resstr = output(x, --numberofop);

                }
                else
                {
                    if (parentoperator != "AND" && parentoperator != "OR" && parentoperator != "NAND" && parentoperator != "NOR" && parentoperator != "XOR")
                    {
                        cout << "Wrong Logic Circuit Description" << endl;
                        exit(0);
                    }
                    else
                    {
                        string firstoperand = operation.substr(childoperation.length() + 1, 1);
                        if (firstoperand != "0" && firstoperand != "1")
                        {
                            cout << "result : BAD input : missing input number" << endl;
                            exit(0);

                        }
                        //cout << firstoperand << endl;
                        string secondoperand = operation.substr(childoperation.length() + 3, 1);
                        if (secondoperand != "0" && secondoperand != "1")
                        {
                            cout << "result : BAD input : missing input number" << endl;
                            exit(0);

                        }
                        //cout << secondoperand << endl;
                        int res = logicalop(childoperation, firstoperand, secondoperand);
                        //cout<<res<<endl;
                        string tempresstr = to_string(res);
                        x.replace(x.find(' ') + 3, (x.find('e')) - (x.find(' ') + 3), tempresstr + " ");
                        //cout<<x<<endl;
                        resstr = output(x, --numberofop);
                    }

                }
            }

        }
        else
        {
            operation = x.substr(parentoperator.length() + 1, (x.find('e') - (x.find(' ') + 1) + 1));
            int countchildoperations = 0;
            string childopres = "";
            int numand = numberoflogicalgates(operation, "AND");
            countchildoperations += numand;
            numand = numberoflogicalgates(operation, "OR");
            countchildoperations += numand;
            numand = numberoflogicalgates(operation, "NOT");
            countchildoperations += numand;
            numand = numberoflogicalgates(operation, "XOR");
            countchildoperations += numand;
            numand = numberoflogicalgates(operation, "NAND");
            countchildoperations += numand;
            numand = numberoflogicalgates(operation, "NOR");
            countchildoperations += numand;
            if (countchildoperations > 1)
            {
                int nthe = findNthOccur(x, 'e', countchildoperations);
                operation = x.substr(parentoperator.length() + 1, (nthe - (x.find(' ') + 1) + 1));
                int numand = numberoflogicalgates(operation, "AND");
                countchildoperations = 0;

                countchildoperations += numand;
                numand = numberoflogicalgates(operation, "OR");
                countchildoperations += numand;
                numand = numberoflogicalgates(operation, "NOT");
                countchildoperations += numand;
                numand = numberoflogicalgates(operation, "XOR");
                countchildoperations += numand;
                numand = numberoflogicalgates(operation, "NAND");
                countchildoperations += numand;
                numand = numberoflogicalgates(operation, "NOR");
                countchildoperations += numand;
                nthe = findNthOccur(x, 'e', countchildoperations);
                //cout<<"op"<<operation<<endl;
                childopres = output(operation, count(operation, 'e'));
                x.replace(x.find(' ') + 1, (nthe - (x.find(' ') + 1) + 1), childopres);
                // cout<<"x" <<x<<endl;
                resstr = output(x, count(x, 'e'));
            }
            else
            {
                string childoperation = operation.substr(0, operation.find(' '));
                //cout << childoperation << endl;
                if (childoperation == "NOT")
                {
                    string firstoperand = operation.substr(childoperation.length() + 1, 1);
                    if (firstoperand != "0" && firstoperand != "1")
                    {
                        cout << "result : BAD input : missing input number" << endl;
                        exit(0);
                    }
                    int res = !stoi(firstoperand);
                    string tempresstr = to_string(res);
                    x.replace(x.find(' ') + 1, (x.find('e') - (x.find(' ') + 1) + 1), tempresstr);
                    //cout<<x<<endl;
                    resstr = output(x, --numberofop);

                }
                else
                {
                    if (parentoperator != "AND" && parentoperator != "OR" && parentoperator != "NAND" && parentoperator != "NOR" && parentoperator != "XOR")
                    {
                        cout << "Wrong Logic Circuit Description" << endl;
                        exit(0);
                    }
                    else
                    {
                        string firstoperand = operation.substr(childoperation.length() + 1, 1);
                        //cout << firstoperand << endl;
                        if (firstoperand != "0" && firstoperand != "1")
                        {
                            cout << "result : BAD input : missing input number" << endl;
                            exit(0);
                        }
                        string secondoperand = operation.substr(childoperation.length() + 3, 1);
                        if (secondoperand != "0" && secondoperand != "1")
                        {
                            cout << "result : BAD input : missing input number" << endl;
                            exit(0);
                        }
                        //cout << secondoperand << endl;
                        int res = logicalop(childoperation, firstoperand, secondoperand);
                        //cout<<res<<endl;
                        string tempresstr = to_string(res);
                        x.replace(x.find(' ') + 1, (x.find('e') - x.find(' ') + 1), tempresstr + " ");
                        //cout<<x<<endl;
                        resstr = output(x, --numberofop);

                    }
                }
            }
        }

    }
    return resstr;
}
string removeDuplicateLetters(string s) {
    string ans = "";
    for (int i = 0; i < s.length(); i++) {
        int j = 0;
        for (j = 0; j < i; j++) {
            if (s[i] == s[j]) 
            {
                break;
            }
        }
        if (i == j) {
            ans += s[i];
        }
    }
    return ans;
}
int main() {
    //string x = "NOR 0 0 e";
    //string x = "AND OR 0 0 e 1 e";
    //string x = "AND 1 OR 1 0 e e";
    //string x = "AND 1 NOT 1 e e";

    //string x = "AND OR 1 0 e OR 0 0 e e";
    string x = "";
    string inputchars = "";
    //cout << "Input Operation" << endl;
    getline(cin, x);
    int countalpha = 0;
    for (int i = 1; i < x.length() - 1; i++)
    {
        if (isalpha(x.at(i)) && (x.at(i - 1) == ' ' && x.at(i + 1) == ' ') && x.at(i) != 'e')
        {
            countalpha++;
            inputchars += (x.at(i));
        }
    }
    inputchars = removeDuplicateLetters(inputchars);
    
    if (inputchars.length() != 0)
    {
        cout << inputchars.length() << " " << "varaibles are missing please enter them in separate lines" << endl;
        for (int i = 0; i < inputchars.length(); i++)
        {
            string missingchars = "";
            cin >> missingchars;
            for (int j = 1; j < x.length()-1; j++)
            {
                //cout << j << endl;
                if (x.at(j) == inputchars.at(i))
                {
                    //cout << j + 1 <<" " << j - 1 << " " << x.at(j + 1) << endl << x.at(j - 1) << endl;
                    
                    if ((x.at(j + 1) == ' ' )&& (x.at(j - 1) == ' '))
                    {
                        //cout << x.at(j + 1) << endl << x.at(j - 1) << endl;
                        //cout<< x.find(x.at(j) )<<endl;
                        x.replace(j, 1, missingchars.substr(missingchars.find('=') + 1, 1));
                    }
                  // cout << x << endl;
                }
            }
        }
    }
    //cout<<x<<endl;


    string o = output(x, count(x, 'e'));
    //cout << o << endl;


    int numand = numberoflogicalgates(x, "AND");
    cout << "AND gates : " << numand << endl;
    numand = numberoflogicalgates(x, "OR");
    cout << "OR gates : " << numand << endl;
    numand = numberoflogicalgates(x, "NOT");
    cout << "NOT gates : " << numand << endl;
    numand = numberoflogicalgates(x, "XOR");
    cout << "XOR gates : " << numand << endl;
    numand = numberoflogicalgates(x, "NAND");
    cout << "NAND gates : " << numand << endl;
    numand = numberoflogicalgates(x, "NOR");
    cout << "NOR gates : " << numand << endl;


    cout << "result : " << o << endl;



    return 0;
}

