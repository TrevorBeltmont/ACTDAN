#include<iostream>
#include<fstream>
#include<string>
#include<map>

using namespace std;

/*
    Checklist:
    1. Abra el archivo de entrada llamado "bitacora.txt" 
       lealo y almacene los datos en una lista doblemente ligada (creada de manera dinámica) (Formato del archivo bitacora.pdf). ✔
    2. Ordene la información por IP para la realización de las búsquedas (CUIDADO con números de dos y tres digitos, 
       orden numérico no alfabético). Si hay dos o más accesos desde una misma dirección IP, el segundo criterio de ordenamiento 
       es la fecha y hora de acceso. En caso de existir otro empate, el tercer criterio es el mensaje de error.
    3. Solicite al usuario las IPs de inicio y fin de búsqueda de información. (la entrada es como un string, 
       primero uno, <enter> y luego otro <enter>).
    4. Despliegue los registros correspondientes a esas IPs, en la salida estándar, de manera descendente, 
       por IP (segundo criterio es la fecha y hora, primero los de Dic, Nov, Oct, Sept ).
    5. Almacenar en un archivo llamado SortedData.txt el resultado del ordenamiento de manera ascendente por IP, 
       (segundo criterio es la fecha Junio, Julio, Agosto, Sept, Oct, ...) mismos criterios de ordenamiento.
*/

struct Node{
    int time;
    string data;
    int month;
    int day;

    Node* next;
    Node* prev;
};

// BUBBLESORT
void bubbleSort(Node** head, int list_size){
    bool condition = true;
    Node* iterator = *head;
    Node* aux = NULL;
    Node* aux_2 = NULL;

    for(int i = 0; i < list_size - 1; i++){
        condition = false;
        for(int j = 0; j < list_size - 1 - i; j++){
            if(iterator->next->day < iterator->day){
                aux = iterator->next->next;
                aux_2 = iterator->next;
                iterator = iterator -> next; // Cambio 5 x 4
                iterator->prev= aux_2;
                aux_2 -> next = iterator;
                iterator->next = aux;
            }
        }
    }
}

// MAPS 
void createMap(map<int, string> &mapa){
    mapa.insert(pair<int, string>(1, "Jan"));
    mapa.insert(pair<int, string>(2, "Feb"));
    mapa.insert(pair<int, string>(3, "Mar"));
    mapa.insert(pair<int, string>(4, "Apr"));
    mapa.insert(pair<int, string>(5, "May"));
    mapa.insert(pair<int, string>(6, "Jun"));
    mapa.insert(pair<int, string>(7, "Jul"));
    mapa.insert(pair<int, string>(8, "Aug"));
    mapa.insert(pair<int, string>(9, "Sep"));
    mapa.insert(pair<int, string>(10, "Oct"));
    mapa.insert(pair<int, string>(11, "Nov"));
    mapa.insert(pair<int, string>(12, "Dec"));
}

// NODES
void pushbackNode(Node** head, int time, string context, int day, int month){
    Node* newNode = new Node;
    Node* iterator = *head; // Iterator takes value of the first node
    newNode->data = context;
    newNode->time = time;
    newNode->day = day;
    newNode->month = month;
    newNode->next = NULL;

    // If DLL is empty, set head as NULL
    if(*head == NULL){
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    // IN CASE DLL IS NOT EMPTY
    while(iterator->next != NULL){ // O(n)
        iterator = iterator->next; 
    }

    iterator->next = newNode; // The last node becomes newNode
    newNode->prev = iterator;

    return;
}

void printDLL(Node* aux){ // O(n) 
    while (aux != NULL){ // O(n)
        cout<<aux->data<<endl;
        if(aux->next == NULL)
            break;
        aux = aux->next;
    }
    // cout<<"FINISH\n";
    // while(aux != NULL){
    //     cout<<aux->data<<endl;
    //     if(aux->prev== NULL)
    //         break;
    //     aux = aux->prev;
    // }
}

int main(){
    // Read data from bitacora.txt
    int large, month_int, day_int, time_int, hour_int, min_int, sec_int;
    string line, month_txt, context;
    map<int, string> months;
    struct Node* head = NULL;

    int counter = 0; // <---- FOR TESTING

    createMap(months);

    ifstream dataset;
    dataset.open("bitacora.txt");

    // Linked list creation
    while(!dataset.eof()){
        getline(dataset, line);
        large = line.length();
        month_txt = line.substr(0,3);
        // Change from month as a string to month as an integer
        for(auto x: months){
            if(x.second == month_txt){
                month_int = x.first;
            }
        }

        day_int = stoi(line.substr(4, 2));    
        hour_int = stoi(line.substr(7, 2));   
        min_int = stoi(line.substr(10, 2));      
        sec_int = stoi(line.substr(13, 2));     
        context = line.substr(0, large);
        time_int = sec_int+(min_int*60)+(hour_int*3600)+(day_int*86400)+(month_int*2592000);

        // Insertion of the new node to the end of the list
        if(counter < 5)
            pushbackNode(&head, time_int, context, day_int, month_int);
        counter++;
    }

    bubbleSort(&head, 5);
    printDLL(head);

    return 0;
}