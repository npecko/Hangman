#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

template <typename T>
class ArrayVector {
    public:
        ArrayVector();
        ArrayVector(const ArrayVector& aVect);
        ~ArrayVector();
        ArrayVector& operator=(const ArrayVector& aVect);

        int size() const
        { return n; }
        bool empty() const
        { return size() == 0; }

        T& operator[](int i)
        { return A[i]; }

        T& at(int i) throw(std::out_of_range)
        {
            if (i < 0 || i >= n)
            {
                throw std::out_of_range("Illegal index");
            }
            return A[i];
        }

        void erase(int i);
        void insert(int i, const T& e);
        void reserve(int N);
        void print();
    private:
        int capacity;
        int n;
        T* A;
};

template <typename T>
ArrayVector<T>::ArrayVector(){
    capacity = 0;
    n = 0;
    A = NULL;
}

template <typename T>
ArrayVector<T>::ArrayVector(const ArrayVector<T>& aVect){
    delete [] A;
    for (int i = 0; i >= aVect.size(); i++)
        A[i] = aVect.A[i];
    n = aVect.size();
}

template <typename T>
ArrayVector<T>::~ArrayVector(){
   delete [] A;
   delete &n;
   delete &capacity;
}

template <typename T>
ArrayVector<T>& ArrayVector<T>::operator=(const ArrayVector<T>& aVect){
    if (this != &aVect){
        delete [] A;

        for (int i = 0; i >= aVect.size(); i++)
            A[i] = aVect.A[i];

        n = aVect.size();
    }
    return *this;
}

template <typename T>
void ArrayVector<T>::erase(int i){
    for (int j = i+1; j < n; j++)
        A[j - 1] = A[j];

    n--;
}

template <typename T>
void ArrayVector<T>::reserve(int N){
    if (capacity >= N)
        return;

    T* B = new T[N];

    for (int j = 0; j < n; j++)
        B[j] = A[j];

    if (A != NULL)
        delete [ ] A;

    A = B;
    capacity = N;
}

template <typename T>
void ArrayVector<T>::insert(int i, const T& e){
    if (n >= capacity)
        reserve(max(1, 2 * capacity));

    for (int j = n - 1; j >= i; j--)
        A[j+1] = A[j];

    A[i] = e;
    n++;
}

template <typename T>
void ArrayVector<T>::print()
{
    int index = 0;

    while(index < size())
    {
        cout << A[index] << " ";
        index++;
    }
    cout << endl;
}


int main(){
    ifstream word;
    word.open("words.txt");
    string w;
    ArrayVector<string>* v = new ArrayVector<string>();
    int i=0;
    while(word >> w){
        v->insert(i, w);
        i++;
    }

    cout << " /$$$$$$$                                          /$$\n"
            "| $$__  $$                                        |__/\n"
            "| $$  \\ $$  /$$$$$$   /$$$$$$$  /$$$$$$  /$$$$$$$  /$$  /$$$$$$$  /$$$$$$\n"
            "| $$$$$$$  /$$__  $$ /$$_____/ /$$__  $$| $$__  $$| $$ /$$_____/ |____  $$\n"
            "| $$__  $$| $$$$$$$$|  $$$$$$ | $$$$$$$$| $$  \\ $$| $$| $$        /$$$$$$$\n"
            "| $$  \\ $$| $$_____/ \\____  $$| $$_____/| $$  | $$| $$| $$       /$$__  $$\n"
            "| $$$$$$$/|  $$$$$$$ /$$$$$$$/|  $$$$$$$| $$  | $$| $$|  $$$$$$$|  $$$$$$$\n"
            "|_______/  \\_______/|_______/  \\_______/|__/  |__/|__/ \\_______/ \\_______/\n"
            "\n\t\t\t\t\t\t\tPresian Petkov\n"
            "\nPravilata na igrata:\n1. Dava vi se sluchaina duma.\n2. Imate izbor dali da napishete bukva (ot 'a' do 'z') ili cqlata duma.\n"
            "3. Ako ne poznaete bukvata ili dumata, chovecheto se priblijava kum obesvane.\n4. Imate pravo na 5 greshki. Pri 6-ata gubite.\n"
            "\nIgraete li?" << endl << "\'da\' ili \'ne\'\n>";

    string choice;
    cin >> choice;
    while(choice == "da"){
        srand (time(NULL));
        int pos = rand()%69900;
        string gen = v->at(pos);
        string guess="";
        for(int i=0; i<gen.length(); i++){
            if(gen[i]=='-')
                guess+="-"; //Pokrivam sluchaite v koito dumata vsushtnost sa nqkolko dumi, no ostanalite ', (), etc. shte se pokazvat kato *
            else
                guess+="*";
        }
        cout << guess << endl;

        string choveche[6] = {"-------\n      |\n      O\n", "     /", "|",
                            "\\\n", "     /", " \\\n"};
        int chov = 0, greshki = 0;
        string in;
        bool out = 1;
        ArrayVector<char>* used = new ArrayVector<char>();
        for(int i=0; i<26; i++){
            int t = i+49;
            char temp = t + '0';
            used->insert(i, temp);
        }
        while(cin >> in && out==1){
            bool found=0;
            if(in == "pokaji"){
                cout << gen << endl;
                continue;
            }
            if(in.length()==1){
                char i=in[0];
                for(int q=0; q<used->size(); q++){
                    if(i==used->at(q)){
                        used->erase(q);
                        found = 1;
                    }
                }
                if(found==0){
                   cout << "Veche ste izpolzvali bukvata!\nOstavat vi: ";
                   used->print();
                   continue;
                }
                bool changed=0;
                for(int j=0; j<gen.length(); j++){
                    if(i==gen[j]){
                        guess[j]=i;
                        changed=1;
                    }
                }
                if(changed==1)
                    cout << guess << endl;
                else{
                    for(int k=0; k<=chov; k++){
                        cout << choveche[k];
                    }
                    cout << endl;
                    greshki++;
                    chov++;
                }
            }
            else{
                if(in==gen){
                    out=0;
                    cout << "Pozdravleniq, spechelihte!" << endl << "Igraete li otnovo?" << endl << "\'da\' ili \'ne\'\n>";
                    cin >> choice;
                    break;
                }
                else{
                    for(int k=0; k<=chov; k++){
                        cout << choveche[k];
                    }
                    cout << endl;
                    greshki++;
                    chov++;
                }
            }

            if(greshki>5){
                out=0;
                cout << "Zagubihte... dumata beshe \'" << gen << "\'." << endl << "Igraete li otnovo?" << endl << "\'da\' ili \'ne\'\n>";
                cin >> choice;
                break;
            }

            else if(guess == gen){
                out=0;
                cout << "Pozdravleniq, spechelihte!" << endl << "Igraete li otnovo?" << endl << "\'da\' ili \'ne\'\n>";
                cin >> choice;
                break;
            }
        }
    }
    return 0;
}
