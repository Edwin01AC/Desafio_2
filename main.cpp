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

class Album {
private:
    string id;
    string nombre;
    string fechaLanzamiento;
    int duracionTotal;
    string selloDisquero;
    float puntuacion;
    string rutaPortada;
    string* generos;
    int numGeneros;

    Cancion** canciones;
    int numCanciones;
    int capacidadCanciones;

    void redimensionarCanciones(int nuevaCapacidad) {
        Cancion** nuevasCanciones = new Cancion*[nuevaCapacidad];

        for (int i = 0; i < numCanciones; i++) {
            nuevasCanciones[i] = canciones[i];
        }

        delete[] canciones;
        canciones = nuevasCanciones;
        capacidadCanciones = nuevaCapacidad;
    }

public:
    Album(const string& id, const string& nom, const string& fecha,
          const string& sello, const string& rutaPortada)
        : id(id), nombre(nom), fechaLanzamiento(fecha), duracionTotal(0),
        selloDisquero(sello), puntuacion(0.0), rutaPortada(rutaPortada),
        numGeneros(0), numCanciones(0), capacidadCanciones(10) {

        generos = new string[4];
        canciones = new Cancion*[capacidadCanciones];
    }

    ~Album() {
        for (int i = 0; i < numCanciones; i++) {
            delete canciones[i];
        }
        delete[] canciones;
        delete[] generos;
    }

    string getId() const { return id; }
    string getNombre() const { return nombre; }
    string getFechaLanzamiento() const { return fechaLanzamiento; }
    int getDuracionTotal() const { return duracionTotal; }
    string getSelloDisquero() const { return selloDisquero; }
    float getPuntuacion() const { return puntuacion; }
    string getRutaPortada() const { return rutaPortada; }
    int getNumCanciones() const { return numCanciones; }

    void setPuntuacion(float punt) {
        if (punt >= 1.0 && punt <= 10.0) {
            puntuacion = punt;
        }
    }

    void setSelloDisquero(const string& sello) { selloDisquero = sello; }

    void agregarGenero(const string& genero) {
        if (numGeneros >= 4) {
            cout << "No se pueden agregar más de 4 géneros" << endl;
            return;
        }
        generos[numGeneros++] = genero;
    }

    void eliminarGenero(int indice) {
        if (indice >= 0 && indice < numGeneros) {
            for (int i = indice; i < numGeneros - 1; i++) {
                generos[i] = generos[i + 1];
            }
            numGeneros--;
        }
    }

    string getGenero(int indice) const {
        if (indice >= 0 && indice < numGeneros) {
            return generos[indice];
        }
        return "";
    }

    int getNumGeneros() const { return numGeneros; }

    void agregarCancion(Cancion* cancion) {
        if (numCanciones >= capacidadCanciones) {
            redimensionarCanciones(capacidadCanciones * 2);
        }

        canciones[numCanciones] = cancion;
        numCanciones++;

        duracionTotal += cancion->getDuracion();
    }

    Cancion* getCancion(int indice) const {
        if (indice >= 0 && indice < numCanciones) {
            return canciones[indice];
        }
        return nullptr;
    }

    Cancion* buscarCancionPorId(const string& idCancion) const {
        for (int i = 0; i < numCanciones; i++) {
            if (canciones[i]->getId() == idCancion) {
                return canciones[i];
            }
        }
        return nullptr;
    }

    void eliminarCancion(int indice) {
        if (indice >= 0 && indice < numCanciones) {
            duracionTotal -= canciones[indice]->getDuracion();

            delete canciones[indice];

            for (int i = indice; i < numCanciones - 1; i++) {
                canciones[i] = canciones[i + 1];
            }
            numCanciones--;
        }
    }

    string getDuracionFormateada() const {
        int minutos = duracionTotal / 60;
        int segundos = duracionTotal % 60;
        return to_string(minutos) + ":" + (segundos < 10 ? "0" : "") + to_string(segundos);
    }

    void mostrarInfo() const {
        cout << "=== ÁLBUM ===" << endl;
        cout << "ID: " << id << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Fecha: " << fechaLanzamiento << endl;
        cout << "Duración: " << getDuracionFormateada() << " (" << duracionTotal << " segundos)" << endl;
        cout << "Sello: " << selloDisquero << endl;
        cout << "Puntuación: " << puntuacion << "/10" << endl;
        cout << "Portada: " << rutaPortada << endl;

        cout << "Géneros (" << numGeneros << "): ";
        for (int i = 0; i < numGeneros; i++) {
            cout << generos[i];
            if (i < numGeneros - 1) cout << ", ";
        }
        cout << endl;

        cout << "Canciones (" << numCanciones << "):" << endl;
        for (int i = 0; i < numCanciones; i++) {
            cout << "  " << (i + 1) << ". " << canciones[i]->getNombre()
            << " (" << canciones[i]->getDuracion() << "s)" << endl;
        }
    }

    bool operator==(const Album& otro) const {
        return this->id == otro.id;
    }
};

class Artista {
private:
    string id;
    string nombre;
    int edad;
    string pais;
    int seguidores;
    int posicionTendencias;

    Album** albumes;
    int numAlbumes;
    int capacidadAlbumes;

    void redimensionarAlbumes(int nuevaCapacidad) {
        Album** nuevosAlbumes = new Album*[nuevaCapacidad];

        for (int i = 0; i < numAlbumes; i++) {
            nuevosAlbumes[i] = albumes[i];
        }

        delete[] albumes;
        albumes = nuevosAlbumes;
        capacidadAlbumes = nuevaCapacidad;
    }

public:
    Artista(const string& id, const string& nom, int edad, const string& pais)
        : id(id), nombre(nom), edad(edad), pais(pais), seguidores(0),
        posicionTendencias(0), numAlbumes(0), capacidadAlbumes(10) {

        albumes = new Album*[capacidadAlbumes];
    }

    ~Artista() {
        for (int i = 0; i < numAlbumes; i++) {
            delete albumes[i];
        }
        delete[] albumes;
    }

    string getId() const { return id; }
    string getNombre() const { return nombre; }
    int getEdad() const { return edad; }
    string getPais() const { return pais; }
    int getSeguidores() const { return seguidores; }
    int getPosicionTendencias() const { return posicionTendencias; }
    int getNumAlbumes() const { return numAlbumes; }

    void setSeguidores(int seg) { seguidores = seg; }
    void setPosicionTendencias(int pos) { posicionTendencias = pos; }
    void setEdad(int nuevaEdad) { edad = nuevaEdad; }

    void agregarAlbum(Album* album) {
        if (numAlbumes >= capacidadAlbumes) {
            redimensionarAlbumes(capacidadAlbumes * 2);
        }

        albumes[numAlbumes] = album;
        numAlbumes++;
    }

    Album* getAlbum(int indice) const {
        if (indice >= 0 && indice < numAlbumes) {
            return albumes[indice];
        }
        return nullptr;
    }

    Album* buscarAlbumPorId(const string& idAlbum) const {
        for (int i = 0; i < numAlbumes; i++) {
            if (albumes[i]->getId() == idAlbum) {
                return albumes[i];
            }
        }
        return nullptr;
    }

    Cancion* buscarCancionEnAlbumes(const string& idCancion) const {
        for (int i = 0; i < numAlbumes; i++) {
            Cancion* cancion = albumes[i]->buscarCancionPorId(idCancion);
            if (cancion != nullptr) {
                return cancion;
            }
        }
        return nullptr;
    }

    int getTotalReproducciones() const {
        int total = 0;
        for (int i = 0; i < numAlbumes; i++) {
            for (int j = 0; j < albumes[i]->getNumCanciones(); j++) {
                Cancion* cancion = albumes[i]->getCancion(j);
                if (cancion != nullptr) {
                    total += cancion->getReproducciones();
                }
            }
        }
        return total;
    }

    Cancion** obtenerTodasLasCanciones(int& totalCanciones) const {
        totalCanciones = 0;
        for (int i = 0; i < numAlbumes; i++) {
            totalCanciones += albumes[i]->getNumCanciones();
        }

        Cancion** todasCanciones = new Cancion*[totalCanciones];
        int indice = 0;

        for (int i = 0; i < numAlbumes; i++) {
            Album* album = albumes[i];
            for (int j = 0; j < album->getNumCanciones(); j++) {
                todasCanciones[indice++] = album->getCancion(j);
            }
        }

        return todasCanciones;
    }

    void mostrarInfo() const {
        cout << "=== ARTISTA ===" << endl;
        cout << "ID: " << id << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Edad: " << edad << " años" << endl;
        cout << "País: " << pais << endl;
        cout << "Seguidores: " << seguidores << endl;
        cout << "Posición en tendencias: " << posicionTendencias << endl;
        cout << "Total reproducciones: " << getTotalReproducciones() << endl;

        cout << "Álbumes (" << numAlbumes << "):" << endl;
        for (int i = 0; i < numAlbumes; i++) {
            cout << "  " << (i + 1) << ". " << albumes[i]->getNombre()
            << " (" << albumes[i]->getNumCanciones() << " canciones)" << endl;
        }
    }

    void mostrarDiscografiaCompleta() const {
        cout << "=== DISCOGRAFÍA DE " << nombre << " ===" << endl;
        for (int i = 0; i < numAlbumes; i++) {
            cout << "\n--- Álbum " << (i + 1) << " ---" << endl;
            albumes[i]->mostrarInfo();
        }
    }

    bool operator==(const Artista& otro) const {
        return this->id == otro.id;
    }

    bool operator<(const Artista& otro) const {
        return this->seguidores < otro.seguidores;
    }
};

int main() {
    cout << "=== PRUEBA DE TODAS LAS CLACES EN CONJUNTO ===" << endl;

    Artista* artista = new Artista("12345", "Artista de Prueba", 25, "Colombia");
    artista->setSeguidores(15000);
    artista->setPosicionTendencias(5);

    Album* album1 = new Album("01", "Primer Álbum", "2023-05-20",
                              "Sello A", "/ruta/portada1.png");
    album1->agregarGenero("Pop");
    album1->agregarGenero("Electrónica");


    Cancion* cancion1 = new Cancion("123450101", "Éxito Uno", 184, "/ruta/base/cancion1");
    cancion1->agregarCredito("Juan", "Pérez", "PROD123456", "Productor");
    album1->agregarCancion(cancion1);

    Cancion* cancion2 = new Cancion("123450102", "Canción Dos", 217, "/ruta/base/cancion2");
    cancion2->agregarCredito("María", "Gómez", "MUSI789012", "Músico");
    album1->agregarCancion(cancion2);

    Album* album2 = new Album("02", "Segundo Álbum", "2024-01-15",
                              "Sello B", "/ruta/portada2.png");
    album2->agregarGenero("Rock");

    Cancion* cancion3 = new Cancion("123450201", "Rock Song", 195, "/ruta/base/cancion3");
    cancion3->agregarCredito("Carlos", "López", "COMP345678", "Compositor");
    album2->agregarCancion(cancion3);

    artista->agregarAlbum(album1);
    artista->agregarAlbum(album2);

    artista->mostrarInfo();

    cout << "\n=== BUSCANDO ÁLBUM ===" << endl;
    Album* albumEncontrado = artista->buscarAlbumPorId("01");
    if (albumEncontrado) {
        cout << "Álbum encontrado: " << albumEncontrado->getNombre() << endl;
    }

    cout << "\n=== BUSCANDO CANCIÓN EN TODOS LOS ÁLBUMES ===" << endl;
    Cancion* cancionEncontrada = artista->buscarCancionEnAlbumes("123450102");
    if (cancionEncontrada) {
        cout << "Canción encontrada: " << cancionEncontrada->getNombre() << endl;
    }

    cout << "\n=== TODAS LAS CANCIONES DEL ARTISTA ===" << endl;
    int totalCanciones;
    Cancion** todasCanciones = artista->obtenerTodasLasCanciones(totalCanciones);
    cout << "Total de canciones: " << totalCanciones << endl;
    for (int i = 0; i < totalCanciones; i++) {
        cout << "  " << (i + 1) << ". " << todasCanciones[i]->getNombre() << endl;
    }
    delete[] todasCanciones;

    cout << "\n=== SIMULANDO REPRODUCCIONES ===" << endl;
    cancion1->incrementarReproducciones();
    cancion1->incrementarReproducciones();
    cancion3->incrementarReproducciones();
    cout << "Total reproducciones del artista: " << artista->getTotalReproducciones() << endl;

    cout << "\n=== DISCROGRAFÍA COMPLETA ===" << endl;
    artista->mostrarDiscografiaCompleta();

    cout << "\n=== SOBRECARGA DE OPERADORES ===" << endl;
    Artista* artista2 = new Artista("67890", "Otro Artista", 30, "México");
    artista2->setSeguidores(8000);

    if (*artista < *artista2) {
        cout << artista->getNombre() << " tiene MENOS seguidores" << endl;
    } else {
        cout << artista->getNombre() << " tiene MÁS seguidores" << endl;
    }

    delete artista;
    delete artista2;

    cout << "\n=== PRUEBA COMPLETADA ===" << endl;
    return 0;
}
