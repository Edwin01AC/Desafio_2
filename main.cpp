#include <iostream>
#include <string>

using namespace std;

class Credito {
private:
    string nombre;
    string apellido;
    string codigoAfiliacion;
    string categoria;

public:
    Credito(const string& nom, const string& ape, const string& cod, const string& cat)
        : nombre(nom), apellido(ape), codigoAfiliacion(cod), categoria(cat) {}

    string getNombre() const { return nombre; }
    string getApellido() const { return apellido; }
    string getCodigoAfiliacion() const { return codigoAfiliacion; }
    string getCategoria() const { return categoria; }

    void setNombre(const string& nom) { nombre = nom; }
    void setApellido(const string& ape) { apellido = ape; }
    void setCodigoAfiliacion(const string& cod) { codigoAfiliacion = cod; }
    void setCategoria(const string& cat) { categoria = cat; }

    void mostrarInfo() const {
        cout << "Nombre: " << nombre << " " << apellido << endl;
        cout << "Código: " << codigoAfiliacion << endl;
        cout << "Categoría: " << categoria << endl;
    }
};

class Cancion {
private:
    string id;
    string nombre;
    int duracion;
    string rutaBaseAudio;
    int reproducciones;

    Credito** creditos;
    int numCreditos;
    int capacidadCreditos;

    void redimensionarCreditos(int nuevaCapacidad) {
        Credito** nuevosCreditos = new Credito*[nuevaCapacidad];

        for (int i = 0; i < numCreditos; i++) {
            nuevosCreditos[i] = creditos[i];
        }

        delete[] creditos;
        creditos = nuevosCreditos;
        capacidadCreditos = nuevaCapacidad;
    }

public:
    Cancion(const string& id, const string& nom, int dur, const string& ruta)
        : id(id), nombre(nom), duracion(dur), rutaBaseAudio(ruta),
        reproducciones(0), numCreditos(0), capacidadCreditos(5) {
        creditos = new Credito*[capacidadCreditos];
    }

    ~Cancion() {
        for (int i = 0; i < numCreditos; i++) {
            delete creditos[i];
        }
        delete[] creditos;
    }

    string getId() const { return id; }
    string getNombre() const { return nombre; }
    int getDuracion() const { return duracion; }
    int getReproducciones() const { return reproducciones; }

    string getRutaAudio128() const {
        return rutaBaseAudio + "_128.ogg";
    }

    string getRutaAudio320() const {
        return rutaBaseAudio + "_320.ogg";
    }

    void agregarCredito(const string& nom, const string& ape,
                        const string& cod, const string& cat) {

        if (numCreditos >= capacidadCreditos) {
            redimensionarCreditos(capacidadCreditos * 2);
        }

        creditos[numCreditos] = new Credito(nom, ape, cod, cat);
        numCreditos++;
    }

    void eliminarCredito(int indice) {
        if (indice >= 0 && indice < numCreditos) {
            delete creditos[indice];
            for (int i = indice; i < numCreditos - 1; i++) {
                creditos[i] = creditos[i + 1];
            }
            numCreditos--;
        }
    }

    int getNumCreditos() const { return numCreditos; }

    Credito* getCredito(int indice) const {
        if (indice >= 0 && indice < numCreditos) {
            return creditos[indice];
        }
        return nullptr;
    }

    void incrementarReproducciones() {
        reproducciones++;
    }

    void mostrarInfo() const {
        cout << "=== CANCIÓN ===" << endl;
        cout << "ID: " << id << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Duración: " << duracion << " segundos" << endl;
        cout << "Reproducciones: " << reproducciones << endl;
        cout << "Ruta 128kbps: " << getRutaAudio128() << endl;
        cout << "Ruta 320kbps: " << getRutaAudio320() << endl;

        cout << "Créditos (" << numCreditos << "):" << endl;
        for (int i = 0; i < numCreditos; i++) {
            cout << "  " << (i + 1) << ". ";
            creditos[i]->mostrarInfo();
        }
    }

    bool operator==(const Cancion& otra) const {
        return this->id == otra.id;
    }
};

int main() {
    cout << "=== PRUEBA CLASE CANCIÓN Y CRÉDITO ===" << endl;

    Cancion* cancion1 = new Cancion("123450101", "Mi Canción", 3, "cancion");

    cancion1->agregarCredito("Juan", "Pérez", "PROD123456", "Productor");
    cancion1->agregarCredito("María", "Gómez", "MUSI789012", "Músico");
    cancion1->agregarCredito("Carlos", "López", "COMP345678", "Compositor");

    cancion1->mostrarInfo();

    cancion1->incrementarReproducciones();
    cancion1->incrementarReproducciones();
    cout << "\nDespués de 2 reproducciones:" << endl;
    cancion1->mostrarInfo();

    return 0;
}
