#include <iostream>

using namespace std;
const char* nombre_archivo = "notas.dat"; // nombre del archivo donde se almacenarán los datos

struct Estudiante {
    int id;
    char nombres[50];
    char apellidos[50];
    double notas[4];
    double promedio;
    char resultado[10];
};

void Crear(Estudiante* estudiantes, int n) {
     system("cls"); 
    FILE* archivo = fopen(nombre_archivo,"a+b");
    for (int i = 0; i < n; i++) {
        estudiantes[i].id = i + 1;
        cin.ignore();
        cout << "Ingrese nombres del estudiante " << i + 1 << ": ";
        cin.getline(estudiantes[i].nombres, 50);
        cout << "Ingrese apellidos del estudiante " << i + 1 << ": ";
        cin.getline(estudiantes[i].apellidos, 50);
        for (int j = 0; j < 4; j++) {
            cout << "Ingrese nota " << j + 1 << " del estudiante " << i + 1 << ": ";
            cin >> estudiantes[i].notas[j];
            estudiantes[i].promedio += estudiantes[i].notas[j];
        }
        estudiantes[i].promedio /= 4;
        if (estudiantes[i].promedio >= 60) {
            strcpy(estudiantes[i].resultado, "APROBADO");
        }
        else {
            strcpy(estudiantes[i].resultado, "REPROBADO");
        }
        fwrite(&estudiantes[i], sizeof(Estudiante), 1, archivo); 
    }
    fclose(archivo);
}

void Leer() {
     system("cls"); 
    FILE* archivo = fopen(nombre_archivo,"rb"); 
    if (!archivo){
    archivo = fopen(nombre_archivo,"w+b"); 
    }
   Estudiante estudiante; 
    int id=0; 
    fread(&estudiante,sizeof(Estudiante),1,archivo);
    cout<<"____________________________________________________________"<<endl;
    cout<<"ID"<<"|"<<" Nombres "<<"|"<<"   Apellidos   "<<"|"<<"    N1 "<<"|"<<" N2"<<"|"<<" N3"<<"|"<<"N4"<<"|"<<" Promedio "<<"|"<<"  Resultado "<<endl;

    do
    {
        cout<<id<<"|"<<estudiante.nombres<<"|"<<estudiante.apellidos<<"|"<<estudiante.notas[0]<<"|"<<estudiante.notas[1]<<"|"<<estudiante.notas[2]<<"|"<<estudiante.notas[3]<<"|    "<<estudiante.promedio<<"|      "<<estudiante.resultado<<endl;
        id+=1;
        fread(&estudiante,sizeof(Estudiante),1,archivo);
    } while (feof(archivo)==0);
    fclose(archivo);
}
 
void Actualizar(Estudiante * estudiantes, int n){ //sobreescribe los datos. Borrar para despues crear. 
FILE* archivo = fopen(nombre_archivo,"r+b"); 
    int id=0;
    cout<<"Ingrese el ID que desea modificar: ";
    cin>>id;
    fseek(archivo,id * sizeof(Estudiante),SEEK_SET); //Sirve para ubicar mi puntero en una determinada posicion //SEEK_SET POSICIONARNOS PARA POSTERIORMENTE SOBREESCRIBIR
for (int i = 0; i < n; i++) {
        estudiantes[i].id = i + 1;
        cin.ignore();
        cout << "Ingrese nombres del estudiante " << i + 1 << ": ";
        cin.getline(estudiantes[i].nombres, 50);
        cout << "Ingrese apellidos del estudiante " << i + 1 << ": ";
        cin.getline(estudiantes[i].apellidos, 50);
        for (int j = 0; j < 4; j++) {
            cout << "Ingrese nota " << j + 1 << " del estudiante " << i + 1 << ": ";
            cin >> estudiantes[i].notas[j];
            estudiantes[i].promedio += estudiantes[i].notas[j];
        }
        estudiantes[i].promedio /= 4;
        if (estudiantes[i].promedio >= 60) {
            strcpy(estudiantes[i].resultado, "APROBADO");
        }
        else {
            strcpy(estudiantes[i].resultado, "REPROBADO");
        }
        fwrite(&estudiantes[i], sizeof(Estudiante), 1, archivo); 
    }  
    fclose(archivo);
    Leer();
}

void Borrar(){
    const char *nombre_archivo_temp = "notas_temp.dat"; // Nombre del archivo temporal
    FILE* archivo = fopen(nombre_archivo,"rb"); 
    FILE* archivo_temp = fopen(nombre_archivo_temp,"w+b"); 
    Estudiante estudiante;
    int id=0, id_n=0;
    cout<<"Ingrese el ID a eliminar: ";
    cin>>id;
    while (fread(&estudiante,sizeof(Estudiante),1,archivo)){
        if (id_n!=id){
            fwrite(&estudiante,sizeof(Estudiante),1,archivo_temp);
        }
        id_n++;
    }
    fclose(archivo);
    fclose(archivo_temp);

    remove(nombre_archivo); // Elimina el archivo original
    rename(nombre_archivo_temp, nombre_archivo); // Renombra el archivo temporal al archivo original

    archivo = fopen(nombre_archivo,"rb"); // Abre el archivo original nuevamente
    cout << "____________________________________________________________" << endl;
    cout << "ID" << "|" << " Nombres " << "|" << "   Apellidos   " << "|" << "    N1 " << "|" << " N2" << "|" << " N3" << "|" << "N4" << "|" << " Promedio " << "|" << "  Resultado " << endl;

    while (fread(&estudiante,sizeof(Estudiante),1,archivo)){
        cout << estudiante.id << "|" << estudiante.nombres << "|" << estudiante.apellidos << "|" << estudiante.notas[0] << "|" << estudiante.notas[1] << "|" << estudiante.notas[2] << "|" << estudiante.notas[3] << "|    " << estudiante.promedio << "|      " << estudiante.resultado << endl;
    }
    fclose(archivo);
}


int main() {
    char r;
    int opcion;
    do{
    int n;
    cout << "Ingrese el numero de estudiantes que desea registrar: ";
    cin >> n;
    cout<<"Programa para calcular el promedio de notas de N estudiantes - Por Sebastian Holweger"<<endl;
    cout<<"======================================================================================"<<endl;
    cout<<" Elija una opción para el CRUD: 1. Crear 2. Leer 3. Actualizar 4. Borrar"<<endl;
    cin>>opcion;
    Estudiante* estudiantes = new Estudiante[n]; // arreglo dinámico de estudiantes
    switch (opcion)
    {
    case 1:
    Crear(estudiantes, n);//Guardar en archivo
        break;
    case 2:
    Leer(); // mostrar los datos del archivo
        break;
    case 3:
    Actualizar(estudiantes,n);

        break;
    case 4:
    Borrar();
        break;
    default:
        break;
    }
    delete[] estudiantes; // liberar la memoria del arreglo dinámico
    cout<<"¿Desea continuar? (s/n)"<<endl;
    cin>>r;
    }while(r=='S'|r=='s');
    return 0;
}
