#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

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
    string getCategoria() const { return categoria; }
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
    string getRutaAudio128() const { return rutaBaseAudio + "_128.ogg"; }
    string getRutaAudio320() const { return rutaBaseAudio + "_320.ogg"; }

    void agregarCredito(const string& nom, const string& ape,
                        const string& cod, const string& cat) {
        if (numCreditos >= capacidadCreditos) {
            redimensionarCreditos(capacidadCreditos * 2);
        }
        creditos[numCreditos] = new Credito(nom, ape, cod, cat);
        numCreditos++;
    }

    void incrementarReproducciones() { reproducciones++; }

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
        generos = new string[4]; // Máximo 4 géneros
        canciones = new Cancion*[capacidadCanciones];
    }

    ~Album() {
        for (int i = 0; i < numCanciones; i++) {
            delete canciones[i];
        }
        delete[] canciones;
        delete[] generos;
    }

    string getNombre() const { return nombre; }
    string getRutaPortada() const { return rutaPortada; }
    int getNumCanciones() const { return numCanciones; }

    void setPuntuacion(float punt) {
        if (punt >= 1.0 && punt <= 10.0) {
            puntuacion = punt;
        }
    }

    void agregarGenero(const string& genero) {
        if (numGeneros < 4) {
            generos[numGeneros++] = genero;
        }
    }

    void agregarCancion(Cancion* cancion) {
        if (numCanciones >= capacidadCanciones) {
            redimensionarCanciones(capacidadCanciones * 2);
        }
        canciones[numCanciones++] = cancion;
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

    string getNombre() const { return nombre; }
    int getNumAlbumes() const { return numAlbumes; }

    void setSeguidores(int seg) { seguidores = seg; }
    void setPosicionTendencias(int pos) { posicionTendencias = pos; }

    void agregarAlbum(Album* album) {
        if (numAlbumes >= capacidadAlbumes) {
            redimensionarAlbumes(capacidadAlbumes * 2);
        }
        albumes[numAlbumes++] = album;
    }

    Album* getAlbum(int indice) const {
        if (indice >= 0 && indice < numAlbumes) {
            return albumes[indice];
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

    Album* buscarAlbumDeCancion(const string& idCancion) const {
        for (int i = 0; i < numAlbumes; i++) {
            if (albumes[i]->buscarCancionPorId(idCancion) != nullptr) {
                return albumes[i];
            }
        }
        return nullptr;
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
};

class GestorPublicidad {
private:
    string* categorias;
    string* mensajes;
    int numPublicidades;
    int capacidadPublicidades;
    int indiceActual;

    void redimensionar() {
        capacidadPublicidades *= 2;
        string* nuevasCategorias = new string[capacidadPublicidades];
        string* nuevosMensajes = new string[capacidadPublicidades];

        for (int i = 0; i < numPublicidades; i++) {
            nuevasCategorias[i] = categorias[i];
            nuevosMensajes[i] = mensajes[i];
        }

        delete[] categorias;
        delete[] mensajes;

        categorias = nuevasCategorias;
        mensajes = nuevosMensajes;
    }

public:
    GestorPublicidad() : numPublicidades(0), capacidadPublicidades(10), indiceActual(0) {
        categorias = new string[capacidadPublicidades];
        mensajes = new string[capacidadPublicidades];
    }

    ~GestorPublicidad() {
        delete[] categorias;
        delete[] mensajes;
    }

    bool cargarDesdeArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) return false;

        string linea;
        while (getline(archivo, linea) && numPublicidades < 50) {
            if (linea.empty()) continue;

            size_t pos = linea.find('|');
            if (pos == string::npos) continue;

            if (numPublicidades >= capacidadPublicidades) {
                redimensionar();
            }

            categorias[numPublicidades] = linea.substr(0, pos);
            mensajes[numPublicidades] = linea.substr(pos + 1);
            numPublicidades++;
        }

        archivo.close();
        return numPublicidades > 0;
    }

    void mostrarSiguientePublicidad() {
        if (numPublicidades == 0) return;

        cout << "\n--- PUBLICIDAD ---" << endl;
        cout << mensajes[indiceActual] << endl;
        cout << "--- FIN PUBLICIDAD ---" << endl;

        indiceActual = (indiceActual + 1) % numPublicidades;
    }

    int getNumPublicidades() const { return numPublicidades; }
};

class Usuario {
protected:
    string nickname;
    string tipo;
    string ciudad;
    string pais;
    string fechaInscripcion;

    Cancion** historialReproduccion;
    int numHistorial;
    int capacidadHistorial;

    void redimensionarHistorial(int nuevaCapacidad) {
        Cancion** nuevoHistorial = new Cancion*[nuevaCapacidad];
        for (int i = 0; i < numHistorial; i++) {
            nuevoHistorial[i] = historialReproduccion[i];
        }
        delete[] historialReproduccion;
        historialReproduccion = nuevoHistorial;
        capacidadHistorial = nuevaCapacidad;
    }

public:
    Usuario(const string& nick, const string& tip, const string& ciu,
            const string& pa, const string& fecha)
        : nickname(nick), tipo(tip), ciudad(ciu), pais(pa), fechaInscripcion(fecha),
        numHistorial(0), capacidadHistorial(10) {
        historialReproduccion = new Cancion*[capacidadHistorial];
    }

    ~Usuario() {
        delete[] historialReproduccion;
    }

    string getNickname() const { return nickname; }
    string getTipo() const { return tipo; }

    void agregarAlHistorial(Cancion* cancion) {
        if (numHistorial >= capacidadHistorial) {
            redimensionarHistorial(capacidadHistorial * 2);
        }
        historialReproduccion[numHistorial++] = cancion;
    }

    void mostrarInfo() const {
        cout << "=== USUARIO ===" << endl;
        cout << "Nickname: " << nickname << endl;
        cout << "Tipo: " << tipo << endl;
        cout << "Ciudad: " << ciudad << ", " << pais << endl;
        cout << "Fecha inscripción: " << fechaInscripcion << endl;
    }
};

class UsuarioEstandar : public Usuario {
private:
    int contadorCanciones;
    GestorPublicidad* gestorPublicidad;

public:
    UsuarioEstandar(const string& nick, const string& ciu,
                    const string& pa, const string& fecha, GestorPublicidad* gestorPub)
        : Usuario(nick, "estandar", ciu, pa, fecha),
        contadorCanciones(0), gestorPublicidad(gestorPub) {}

    void reproducirCancion(Cancion* cancion, const string& rutaPortada, const string& artistaNombre) {
        cout << "\n=== REPRODUCIENDO ===" << endl;
        cout << "Artista: " << artistaNombre << endl;
        cout << "Canción: " << cancion->getNombre() << endl;
        cout << "Portada: " << rutaPortada << endl;
        cout << "Audio: " << cancion->getRutaAudio128() << endl;
        cout << "Calidad: 128 kbps" << endl;
        cout << "Direccion de memoria de la cancion: " << cancion << endl;

        cancion->incrementarReproducciones();
        agregarAlHistorial(cancion);

        contadorCanciones++;
        if (contadorCanciones % 2 == 0 && gestorPublicidad != nullptr) {
            gestorPublicidad->mostrarSiguientePublicidad();
        }
    }
};

class UsuarioPremium : public Usuario {
private:
    Cancion** listaFavoritos;
    int numFavoritos;
    int capacidadFavoritos;

    Cancion** historialNavegacion;
    int indiceHistorialNav;
    int maxHistorialNav;

    void redimensionarFavoritos(int nuevaCapacidad) {
        Cancion** nuevosFavoritos = new Cancion*[nuevaCapacidad];
        for (int i = 0; i < numFavoritos; i++) {
            nuevosFavoritos[i] = listaFavoritos[i];
        }
        delete[] listaFavoritos;
        listaFavoritos = nuevosFavoritos;
        capacidadFavoritos = nuevaCapacidad;
    }

public:
    UsuarioPremium(const string& nick, const string& ciu,
                   const string& pa, const string& fecha)
        : Usuario(nick, "premium", ciu, pa, fecha),
        numFavoritos(0), capacidadFavoritos(100),
        indiceHistorialNav(0), maxHistorialNav(4) {

        listaFavoritos = new Cancion*[capacidadFavoritos];
        historialNavegacion = new Cancion*[maxHistorialNav];
        for (int i = 0; i < maxHistorialNav; i++) {
            historialNavegacion[i] = nullptr;
        }
    }

    ~UsuarioPremium() {
        delete[] listaFavoritos;
        delete[] historialNavegacion;
    }

    void mostrarInfo() const {
        Usuario::mostrarInfo();
        cout << "Favoritos: " << numFavoritos << endl;
        cout << "Precio: $19.900 COP/mes" << endl;
    }
};

class Sistema {
private:
    UsuarioEstandar** usuariosEstandar;
    UsuarioPremium** usuariosPremium;
    Artista** artistas;
    GestorPublicidad* gestorPublicidad;

    int numUsuariosEstandar;
    int numUsuariosPremium;
    int numArtistas;
    int capacidadUsuarios;
    int capacidadArtistas;

    string usuarioLogueado;
    string tipoUsuarioLogueado;

    bool validarCredencialPremium(const string& usuario, const string& clave) {
        ifstream archivo("credenciales_premium.txt");
        if (!archivo.is_open()) {
            cout << "Error: No se pudo abrir credenciales_premium.txt" << endl;
            return false;
        }

        string linea;
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;

            size_t pos = linea.find('|');
            if (pos == string::npos) continue;

            string user = linea.substr(0, pos);
            string pass = linea.substr(pos + 1);

            if (user == usuario && pass == clave) {
                archivo.close();
                return true;
            }
        }

        archivo.close();
        return false;
    }

    void cargarDatosIniciales() {
        gestorPublicidad = new GestorPublicidad();
        gestorPublicidad->cargarDesdeArchivo("publicidades.txt");

        cargarUsuariosDesdeArchivo("usuarios.txt");

        crearDatosMusicales();
    }

    void cargarUsuariosDesdeArchivo(const string& archivo) {
        ifstream file(archivo);
        if (!file.is_open()) return;

        string linea;
        while (getline(file, linea)) {
            if (linea.empty()) continue;

            size_t p1 = linea.find('|');
            size_t p2 = linea.find('|', p1 + 1);
            size_t p3 = linea.find('|', p2 + 1);
            size_t p4 = linea.find('|', p3 + 1);

            if (p1 == string::npos || p2 == string::npos ||
                p3 == string::npos || p4 == string::npos) continue;

            string nick = linea.substr(0, p1);
            string tipo = linea.substr(p1 + 1, p2 - p1 - 1);
            string ciudad = linea.substr(p2 + 1, p3 - p2 - 1);
            string pais = linea.substr(p3 + 1, p4 - p3 - 1);
            string fecha = linea.substr(p4 + 1);

            if (tipo == "estandar") {
                usuariosEstandar[numUsuariosEstandar++] =
                    new UsuarioEstandar(nick, ciudad, pais, fecha, gestorPublicidad);
            } else if (tipo == "premium") {
                usuariosPremium[numUsuariosPremium++] =
                    new UsuarioPremium(nick, ciudad, pais, fecha);
            }
        }
        file.close();
    }

    void crearDatosMusicales() {
        Artista* artista1 = new Artista("10001", "Artista Pop", 25, "Colombia");
        artista1->setSeguidores(50000);
        artista1->setPosicionTendencias(3);

        Album* album1 = new Album("01", "Éxitos 2024", "2024-01-15",
                                  "Sello Pop", "/ruta/pop/portada.png");
        album1->agregarGenero("Pop");
        album1->setPuntuacion(8.5);

        Cancion* c1 = new Cancion("100010101", "Canción Verano", 184, "/ruta/pop/cancion1");
        c1->agregarCredito("Juan", "Pérez", "PROD123456", "Productor");
        album1->agregarCancion(c1);

        Cancion* c2 = new Cancion("100010102", "Noche Fiesta", 217, "/ruta/pop/cancion2");
        c2->agregarCredito("María", "Gómez", "COMP789012", "Compositor");
        album1->agregarCancion(c2);

        artista1->agregarAlbum(album1);
        artistas[numArtistas++] = artista1;

        Artista* artista2 = new Artista("10002", "Banda Rock", 32, "México");
        artista2->setSeguidores(75000);
        artista2->setPosicionTendencias(5);

        Album* album2 = new Album("01", "Rock Clásico", "2024-02-20",
                                  "Sello Rock", "/ruta/rock/portada.png");
        album2->agregarGenero("Rock");
        album2->setPuntuacion(9.0);

        Cancion* c3 = new Cancion("100020101", "Guitarra Eléctrica", 245, "/ruta/rock/cancion1");
        album2->agregarCancion(c3);

        Cancion* c4 = new Cancion("100020102", "Ritmo Fuerte", 198, "/ruta/rock/cancion2");
        album2->agregarCancion(c4);

        artista2->agregarAlbum(album2);
        artistas[numArtistas++] = artista2;
    }

    void reproduccionAleatoria() {
        cout << "\n=== REPRODUCCIÓN ALEATORIA ===" << endl;

        int totalCanciones;
        Cancion** todasCanciones = obtenerTodasLasCanciones(totalCanciones);

        if (totalCanciones == 0) {
            cout << "No hay canciones disponibles" << endl;
            return;
        }

        int K = min(5, totalCanciones);
        cout << "Reproduciendo " << K << " canciones aleatorias...\n" << endl;

        for (int i = 0; i < K; i++) {
            int indice = rand() % totalCanciones;
            Cancion* cancion = todasCanciones[indice];

            string artistaNombre = "Desconocido";
            string rutaPortada = "/default/portada.png";

            for (int j = 0; j < numArtistas; j++) {
                Album* album = artistas[j]->buscarAlbumDeCancion(cancion->getId());
                if (album != nullptr) {
                    artistaNombre = artistas[j]->getNombre();
                    rutaPortada = album->getRutaPortada();
                    break;
                }
            }

            if (tipoUsuarioLogueado == "estandar") {
                UsuarioEstandar* user = getUsuarioEstandarActual();
                if (user) user->reproducirCancion(cancion, rutaPortada, artistaNombre);
            } else {
                UsuarioPremium* user = getUsuarioPremiumActual();
                if (user) user->reproducirCancion(cancion, rutaPortada, artistaNombre);
            }

            cout << "Reproduciendo";
            for (int s = 0; s < 3; s++) {
                cout << "." << flush;
                this_thread::sleep_for(chrono::seconds(1));
            }
            cout << " Finalizada\n" << endl;
        }

        delete[] todasCanciones;
    }

    Cancion** obtenerTodasLasCanciones(int& total) {
        total = 0;
        for (int i = 0; i < numArtistas; i++) {
            int temp;
            artistas[i]->obtenerTodasLasCanciones(temp);
            total += temp;
        }

        if (total == 0) return nullptr;

        Cancion** todas = new Cancion*[total];
        int idx = 0;

        for (int i = 0; i < numArtistas; i++) {
            int numCanciones;
            Cancion** canciones = artistas[i]->obtenerTodasLasCanciones(numCanciones);
            for (int j = 0; j < numCanciones; j++) {
                todas[idx++] = canciones[j];
            }
            delete[] canciones;
        }

        return todas;
    }

    UsuarioEstandar* getUsuarioEstandarActual() {
        for (int i = 0; i < numUsuariosEstandar; i++) {
            if (usuariosEstandar[i]->getNickname() == usuarioLogueado) {
                return usuariosEstandar[i];
            }
        }
        return nullptr;
    }

    UsuarioPremium* getUsuarioPremiumActual() {
        for (int i = 0; i < numUsuariosPremium; i++) {
            if (usuariosPremium[i]->getNickname() == usuarioLogueado) {
                return usuariosPremium[i];
            }
        }
        return nullptr;
    }

    Cancion* buscarCancionPorId(const string& id) {
        for (int i = 0; i < numArtistas; i++) {
            Cancion* c = artistas[i]->buscarCancionEnAlbumes(id);
            if (c != nullptr) return c;
        }
        return nullptr;
    }

    void menuFavoritos() {
        UsuarioPremium* user = getUsuarioPremiumActual();
        if (!user) return;

        char op;
        do {
            cout << "\n=== MI LISTA DE FAVORITOS ===" << endl;
            cout << "a. Editar mi lista" << endl;
            cout << "b. Seguir otra lista" << endl;
            cout << "c. Ejecutar mi lista" << endl;
            cout << "d. Volver" << endl;
            cout << "Opción: ";
            cin >> op;
            cin.ignore();

            switch (op) {
            case 'a': {
                cout << "ID de canción: ";
                string id;
                getline(cin, id);
                Cancion* c = buscarCancionPorId(id);
                if (c) {
                    cout << "1. Agregar  2. Eliminar: ";
                    int opt;
                    cin >> opt;
                    cin.ignore();
                    if (opt == 1) user->agregarFavorito(c);
                    else if (opt == 2) user->eliminarFavorito(id);
                } else {
                    cout << "Canción no encontrada" << endl;
                }
                break;
            }
            case 'b': {
                cout << "Nickname del usuario premium a seguir: ";
                string nick;
                getline(cin, nick);
                UsuarioPremium* otro = nullptr;
                for (int i = 0; i < numUsuariosPremium; i++) {
                    if (usuariosPremium[i]->getNickname() == nick) {
                        otro = usuariosPremium[i];
                        break;
                    }
                }
                if (otro && otro != user) {
                    for (int i = 0; i < otro->getNumFavoritos(); i++) {
                        user->agregarFavorito(otro->getFavorito(i));
                    }
                    cout << "Lista seguida exitosamente" << endl;
                } else {
                    cout << "Usuario no encontrado o inválido" << endl;
                }
                break;
            }
            case 'c': {
                cout << "1. Orden original  2. Aleatorio: ";
                int orden;
                cin >> orden;
                cin.ignore();

                int numFav = user->getNumFavoritos();
                if (numFav == 0) {
                    cout << "Lista vacía" << endl;
                    break;
                }

                cout << "\nReproduciendo favoritos (máx 3)..." << endl;
                for (int i = 0; i < min(3, numFav); i++) {
                    int idx = (orden == 2) ? rand() % numFav : i;
                    Cancion* c = user->getFavorito(idx);
                    if (c) {
                        string artista = "Desconocido";
                        string portada = "/default/portada.png";
                        for (int j = 0; j < numArtistas; j++) {
                            Album* album = artistas[j]->buscarAlbumDeCancion(c->getId());
                            if (album) {
                                artista = artistas[j]->getNombre();
                                portada = album->getRutaPortada();
                                break;
                            }
                        }
                        user->reproducirCancion(c, portada, artista);

                        cout << "Reproduciendo";
                        for (int s = 0; s < 3; s++) {
                            cout << "." << flush;
                            this_thread::sleep_for(chrono::seconds(1));
                        }
                        cout << " Finalizada\n" << endl;
                    }
                }
                break;
            }
            case 'd':
                break;
            default:
                cout << "Opción inválida" << endl;
            }
        } while (op != 'd');
    }

public:
    Sistema() : numUsuariosEstandar(0), numUsuariosPremium(0), numArtistas(0),
        capacidadUsuarios(50), capacidadArtistas(20),
        usuarioLogueado(""), tipoUsuarioLogueado("") {

        usuariosEstandar = new UsuarioEstandar*[capacidadUsuarios];
        usuariosPremium = new UsuarioPremium*[capacidadUsuarios];
        artistas = new Artista*[capacidadArtistas];

        cargarDatosIniciales();

        cout << "\n=== SISTEMA UDEATUNES INICIALIZADO ===" << endl;
        cout << "Usuarios cargados: " << (numUsuariosEstandar + numUsuariosPremium) << endl;
        cout << "Artistas cargados: " << numArtistas << endl;
    }

    ~Sistema() {
        for (int i = 0; i < numUsuariosEstandar; i++) {
            delete usuariosEstandar[i];
        }
        delete[] usuariosEstandar;

        for (int i = 0; i < numUsuariosPremium; i++) {
            delete usuariosPremium[i];
        }
        delete[] usuariosPremium;

        for (int i = 0; i < numArtistas; i++) {
            delete artistas[i];
        }
        delete[] artistas;

        delete gestorPublicidad;
    }

    bool iniciarSesion(const string& nickname, const string& clave = "") {
        for (int i = 0; i < numUsuariosEstandar; i++) {
            if (usuariosEstandar[i]->getNickname() == nickname) {
                usuarioLogueado = nickname;
                tipoUsuarioLogueado = "estandar";
                cout << "✓ Sesión iniciada (Estándar)" << endl;
                return true;
            }
        }

        for (int i = 0; i < numUsuariosPremium; i++) {
            if (usuariosPremium[i]->getNickname() == nickname) {
                if (!clave.empty()) {
                    if (validarCredencialPremium(nickname, clave)) {
                        usuarioLogueado = nickname;
                        tipoUsuarioLogueado = "premium";
                        cout << "✓ Sesión iniciada (Premium)" << endl;
                        return true;
                    } else {
                        cout << "✗ Contraseña incorrecta para usuario premium" << endl;
                        return false;
                    }
                } else {
                    cout << "✗ Usuario premium requiere contraseña" << endl;
                    return false;
                }
            }
        }

        cout << "✗ Usuario no encontrado" << endl;
        return false;
    }

    void cerrarSesion() {
        cout << "Sesión cerrada: " << usuarioLogueado << endl;
        usuarioLogueado = "";
        tipoUsuarioLogueado = "";
    }

    void ejecutar() {
        srand(time(0));

        cout << "Bienvenido a UdeATunes" << endl;

        int opcion;
        bool salir = false;

        while (!salir) {
            if (usuarioLogueado.empty()) {
                cout << "\n=== MENÚ PRINCIPAL ===" << endl;
                cout << "1. Iniciar sesión" << endl;
                cout << "2. Salir" << endl;
                cout << "Opción: ";
                cin >> opcion;
                cin.ignore();

                switch (opcion) {
                case 1: {
                    cout << "Nickname: ";
                    string nick;
                    getline(cin, nick);

                    bool esPremium = false;
                    for (int i = 0; i < numUsuariosPremium; i++) {
                        if (usuariosPremium[i]->getNickname() == nick) {
                            esPremium = true;
                            break;
                        }
                    }

                    if (esPremium) {
                        cout << "Contraseña: ";
                        string clave;
                        getline(cin, clave);
                        iniciarSesion(nick, clave);
                    } else {
                        iniciarSesion(nick);
                    }
                    break;
                }
                case 2:
                    salir = true;
                    cout << "¡Hasta pronto!" << endl;
                    break;
                default:
                    cout << "Opción inválida" << endl;
                }
            } else {
                if (tipoUsuarioLogueado == "estandar") {
                    cout << "\n=== USUARIO ESTÁNDAR: " << usuarioLogueado << " ===" << endl;
                    cout << "1. Reproducción aleatoria" << endl;
                    cout << "2. Información de cuenta" << endl;
                    cout << "3. Cerrar sesión" << endl;
                    cout << "Opción: ";
                    cin >> opcion;
                    cin.ignore();

                    switch (opcion) {
                    case 1:
                        reproduccionAleatoria();
                        break;
                    case 2: {
                        UsuarioEstandar* user = getUsuarioEstandarActual();
                        if (user) user->mostrarInfo();
                        break;
                    }
                    case 3:
                        cerrarSesion();
                        break;
                    default:
                        cout << "Opción inválida" << endl;
                    }
                } else if (tipoUsuarioLogueado == "premium") {
                    cout << "\n=== USUARIO PREMIUM: " << usuarioLogueado << " ===" << endl;
                    cout << "1. Reproducción aleatoria" << endl;
                    cout << "2. Mi lista de favoritos" << endl;
                    cout << "3. Información de cuenta" << endl;
                    cout << "4. Cerrar sesión" << endl;
                    cout << "Opción: ";
                    cin >> opcion;
                    cin.ignore();

                    switch (opcion) {
                    case 1:
                        reproduccionAleatoria();
                        break;
                    case 2:
                        menuFavoritos();
                        break;
                    case 3: {
                        UsuarioPremium* user = getUsuarioPremiumActual();
                        if (user) user->mostrarInfo();
                        break;
                    }
                    case 4:
                        cerrarSesion();
                        break;
                    default:
                        cout << "Opción inválida" << endl;
                    }
                }
            }
        }
    }
};

int main() {
    Sistema sistema;
    sistema.ejecutar();
    return 0;
}
