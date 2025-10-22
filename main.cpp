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

class Usuario {
protected:
    string nombre;
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
    Usuario(const string& nom, const string& tip, const string& ciu,
            const string& pa, const string& fecha)
        : nombre(nom), tipo(tip), ciudad(ciu), pais(pa), fechaInscripcion(fecha),
        numHistorial(0), capacidadHistorial(10) {

        historialReproduccion = new Cancion*[capacidadHistorial];
    }

    ~Usuario() {
        delete[] historialReproduccion;
    }

    string getNickname() const { return nombre; }
    string getTipo() const { return tipo; }
    string getCiudad() const { return ciudad; }
    string getPais() const { return pais; }
    string getFechaInscripcion() const { return fechaInscripcion; }
    int getNumHistorial() const { return numHistorial; }

    void setCiudad(const string& ciu) { ciudad = ciu; }
    void setPais(const string& pa) { pais = pa; }

    void agregarAlHistorial(Cancion* cancion) {
        if (numHistorial >= capacidadHistorial) {
            redimensionarHistorial(capacidadHistorial * 2);
        }

        historialReproduccion[numHistorial] = cancion;
        numHistorial++;
    }

    Cancion* getCancionHistorial(int indice) const {
        if (indice >= 0 && indice < numHistorial) {
            return historialReproduccion[indice];
        }
        return nullptr;
    }

    void mostrarInfo() const {
        cout << "=== USUARIO ===" << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Tipo: " << tipo << endl;
        cout << "Ciudad: " << ciudad << endl;
        cout << "País: " << pais << endl;
        cout << "Fecha de inscripción: " << fechaInscripcion << endl;
        cout << "Canciones en historial: " << numHistorial << endl;
    }

    void mostrarHistorial() const {
        cout << "Últimas canciones reproducidas:" << endl;
        for (int i = 0; i < numHistorial; i++) {
            cout << "  " << (i + 1) << ". " << historialReproduccion[i]->getNombre() << endl;
        }
    }

    void reproducirCancionBase(Cancion* cancion, const string& rutaPortada, const string& artistaNombre) {
        cout << "\n=== REPRODUCIENDO CANCIÓN ===" << endl;
        cout << "Cantante: " << artistaNombre << endl;
        cout << "Ruta a la portada del álbum: " << rutaPortada << endl;
        cout << "Título: " << cancion->getNombre() << endl;
        cout << "Duración: " << cancion->getDuracion() << " segundos" << endl;

        cancion->incrementarReproducciones();

        agregarAlHistorial(cancion);
    }

    void mostrarOpcionesBase() const {
        cout << "\n=== OPCIONES DE REPRODUCCIÓN ===" << endl;
        cout << "1.- Reproducir" << endl;
        cout << "2.- Detener" << endl;
    }

    bool operator==(const Usuario& otro) const {
        return this->nombre == otro.nombre;
    }
};

class UsuarioEstandar {
private:
    Usuario usuarioBase;
    int contadorCanciones;
    int totalReproducciones;

public:
    UsuarioEstandar(const string& nick, const string& ciu,
                    const string& pa, const string& fecha)
        : usuarioBase(nick, "estandar", ciu, pa, fecha),
        contadorCanciones(0), totalReproducciones(0) {}

    void reproducirCancion(Cancion* cancion, const string& rutaPortada, const string& artistaNombre) {
        usuarioBase.reproducirCancionBase(cancion, rutaPortada, artistaNombre);

        cout << "Ruta al archivo de audio: " << cancion->getRutaAudio128() << endl;
        cout << "Calidad: 128 kbps" << endl;

        contadorCanciones++;
        if (contadorCanciones % 2 == 0) {
            cout << "\n--- PUBLICIDAD ---" << endl;
            cout << "Mensaje publicitario: ¡Escucha más música sin interrupciones con Premium!" << endl;
            cout << "Categoría del mensaje: B" << endl;
            cout << "--- FIN PUBLICIDAD ---\n" << endl;
        }

        totalReproducciones++;
        cout << "Reproducción completada!" << endl;
    }

    void mostrarOpcionesReproduccion() const {
        usuarioBase.mostrarOpcionesBase();
        cout << "3.- Siguiente canción" << endl;
        cout << "NOTA: Usuarios estándar no pueden volver a canciones anteriores" << endl;
    }

    string getNickname() const { return usuarioBase.getNickname(); }
    string getTipo() const { return usuarioBase.getTipo(); }
    string getCiudad() const { return usuarioBase.getCiudad(); }
    string getPais() const { return usuarioBase.getPais(); }
    string getFechaInscripcion() const { return usuarioBase.getFechaInscripcion(); }
    int getNumHistorial() const { return usuarioBase.getNumHistorial(); }
    Cancion* getCancionHistorial(int indice) const { return usuarioBase.getCancionHistorial(indice); }

    int getTotalReproducciones() const { return totalReproducciones; }
    int getContadorPublicidad() const { return contadorCanciones / 2; }

    void mostrarInfo() const {
        usuarioBase.mostrarInfo();
        cout << "Total reproducciones: " << totalReproducciones << endl;
        cout << "Publicidades mostradas: " << getContadorPublicidad() << endl;
        cout << "Calidad de audio: 128 kbps" << endl;
        usuarioBase.mostrarHistorial();
    }

    bool operator==(const UsuarioEstandar& otro) const {
        return this->usuarioBase == otro.usuarioBase;
    }

    void mostrarResumen() const {
        cout << "Usuario: " << getNickname() << " (" << getTipo() << ")";
    }
};

class UsuarioPremium {
private:
    Usuario usuarioBase;
    int totalReproducciones;

    Cancion** listaFavoritos;
    int numFavoritos;
    int capacidadFavoritos;

    UsuarioPremium** usuariosSeguidos;
    int numUsuariosSeguidos;
    int capacidadUsuariosSeguidos;

    Cancion** cancionesAnteriores;
    int indiceCancionesAnteriores;
    int maxCancionesAnteriores;

    void redimensionarFavoritos(int nuevaCapacidad) {
        Cancion** nuevosFavoritos = new Cancion*[nuevaCapacidad];

        for (int i = 0; i < numFavoritos; i++) {
            nuevosFavoritos[i] = listaFavoritos[i];
        }

        delete[] listaFavoritos;
        listaFavoritos = nuevosFavoritos;
        capacidadFavoritos = nuevaCapacidad;
    }

    void redimensionarUsuariosSeguidos(int nuevaCapacidad) {
        UsuarioPremium** nuevosSeguidos = new UsuarioPremium*[nuevaCapacidad];

        for (int i = 0; i < numUsuariosSeguidos; i++) {
            nuevosSeguidos[i] = usuariosSeguidos[i];
        }

        delete[] usuariosSeguidos;
        usuariosSeguidos = nuevosSeguidos;
        capacidadUsuariosSeguidos = nuevaCapacidad;
    }

public:
    UsuarioPremium(const string& nick, const string& ciu,
                   const string& pa, const string& fecha)
        : usuarioBase(nick, "premium", ciu, pa, fecha),
        totalReproducciones(0), numFavoritos(0), capacidadFavoritos(100),
        numUsuariosSeguidos(0), capacidadUsuariosSeguidos(10),
        indiceCancionesAnteriores(0), maxCancionesAnteriores(4) {

        listaFavoritos = new Cancion*[capacidadFavoritos];
        usuariosSeguidos = new UsuarioPremium*[capacidadUsuariosSeguidos];
        cancionesAnteriores = new Cancion*[maxCancionesAnteriores];

        for (int i = 0; i < maxCancionesAnteriores; i++) {
            cancionesAnteriores[i] = nullptr;
        }
    }

    ~UsuarioPremium() {
        delete[] listaFavoritos;
        delete[] usuariosSeguidos;
        delete[] cancionesAnteriores;
    }

    string getNickname() const { return usuarioBase.getNickname(); }
    string getTipo() const { return usuarioBase.getTipo(); }
    string getCiudad() const { return usuarioBase.getCiudad(); }
    string getPais() const { return usuarioBase.getPais(); }
    string getFechaInscripcion() const { return usuarioBase.getFechaInscripcion(); }
    int getNumHistorial() const { return usuarioBase.getNumHistorial(); }
    Cancion* getCancionHistorial(int indice) const { return usuarioBase.getCancionHistorial(indice); }
    int getNumFavoritos() const { return numFavoritos; }
    int getTotalReproducciones() const { return totalReproducciones; }

    void reproducirCancion(Cancion* cancion, const string& rutaPortada, const string& artistaNombre) {
        usuarioBase.reproducirCancionBase(cancion, rutaPortada, artistaNombre);

        cout << "Ruta al archivo de audio: " << cancion->getRutaAudio320() << endl;
        cout << "Calidad: 320 kbps" << endl;
        cout << "SIN PUBLICIDAD" << endl;

        cancionesAnteriores[indiceCancionesAnteriores] = cancion;
        indiceCancionesAnteriores = (indiceCancionesAnteriores + 1) % maxCancionesAnteriores;

        totalReproducciones++;
        cout << "Reproducción completada!" << endl;
    }

    void mostrarOpcionesReproduccion() const {
        usuarioBase.mostrarOpcionesBase();
        cout << "3.- Siguiente canción" << endl;
        cout << "4.- Canción anterior" << endl;
        cout << "5.- Repetir canción actual" << endl;
    }

    void agregarFavorito(Cancion* cancion) {
        for (int i = 0; i < numFavoritos; i++) {
            if (listaFavoritos[i] == cancion) {
                cout << "La canción ya está en favoritos" << endl;
                return;
            }
        }

        if (numFavoritos >= 10000) {
            cout << "Límite de favoritos alcanzado (10000 canciones)" << endl;
            return;
        }

        if (numFavoritos >= capacidadFavoritos) {
            redimensionarFavoritos(capacidadFavoritos * 2);
        }

        listaFavoritos[numFavoritos] = cancion;
        numFavoritos++;
        cout << "Canción agregada a favoritos" << endl;
    }

    void eliminarFavorito(const string& idCancion) {
        for (int i = 0; i < numFavoritos; i++) {
            if (listaFavoritos[i]->getId() == idCancion) {
                for (int j = i; j < numFavoritos - 1; j++) {
                    listaFavoritos[j] = listaFavoritos[j + 1];
                }
                numFavoritos--;
                cout << "Canción eliminada de favoritos" << endl;
                return;
            }
        }
        cout << "Canción no encontrada en favoritos" << endl;
    }

    Cancion* getFavorito(int indice) const {
        if (indice >= 0 && indice < numFavoritos) {
            return listaFavoritos[indice];
        }
        return nullptr;
    }

    bool esFavorito(const string& idCancion) const {
        for (int i = 0; i < numFavoritos; i++) {
            if (listaFavoritos[i]->getId() == idCancion) {
                return true;
            }
        }
        return false;
    }

    void seguirUsuario(UsuarioPremium* usuario) {
        if (this == usuario) {
            cout << "No puedes seguirte a ti mismo" << endl;
            return;
        }

        for (int i = 0; i < numUsuariosSeguidos; i++) {
            if (usuariosSeguidos[i] == usuario) {
                cout << "Ya sigues a este usuario" << endl;
                return;
            }
        }

        if (numUsuariosSeguidos >= capacidadUsuariosSeguidos) {
            redimensionarUsuariosSeguidos(capacidadUsuariosSeguidos * 2);
        }

        usuariosSeguidos[numUsuariosSeguidos] = usuario;
        numUsuariosSeguidos++;
        cout << "Ahora sigues a: " << usuario->getNickname() << endl;
    }

    Cancion* getCancionAnterior(int posicion) const {
        if (posicion < 0 || posicion >= maxCancionesAnteriores) {
            return nullptr;
        }

        int indice = (indiceCancionesAnteriores - posicion - 1 + maxCancionesAnteriores) % maxCancionesAnteriores;
        return cancionesAnteriores[indice];
    }

    void mostrarInfo() const {
        usuarioBase.mostrarInfo();
        cout << "Total reproducciones: " << totalReproducciones << endl;
        cout << "Canciones en favoritos: " << numFavoritos << endl;
        cout << "Usuarios seguidos: " << numUsuariosSeguidos << endl;
        cout << "Calidad de audio: 320 kbps" << endl;
        cout << "Precio mensual: $19.900 COP" << endl;
        usuarioBase.mostrarHistorial();
    }

    void mostrarFavoritos() const {
        cout << "=== LISTA DE FAVORITOS (" << numFavoritos << " canciones) ===" << endl;
        for (int i = 0; i < numFavoritos; i++) {
            cout << "  " << (i + 1) << ". " << listaFavoritos[i]->getNombre()
            << " (" << listaFavoritos[i]->getId() << ")" << endl;
        }
    }

    void mostrarUsuariosSeguidos() const {
        cout << "=== USUARIOS SEGUIDOS (" << numUsuariosSeguidos << " usuarios) ===" << endl;
        for (int i = 0; i < numUsuariosSeguidos; i++) {
            cout << "  " << (i + 1) << ". " << usuariosSeguidos[i]->getNickname() << endl;
        }
    }

    void mostrarResumen() const {
        cout << "Usuario Premium: " << getNickname() << " - " << numFavoritos << " favoritos";
    }

    bool operator==(const UsuarioPremium& otro) const {
        return this->usuarioBase == otro.usuarioBase;
    }
};

int main() {
    cout << "=== PRUEBA CLASE USUARIO PREMIUM ===" << endl;

    Artista* artista = new Artista("12345", "Artista Premium", 30, "Colombia");
    Album* album = new Album("01", "Álbum Premium", "2024-01-15", "Sello", "/ruta/portada.png");

    Cancion* cancion1 = new Cancion("123450101", "Hit Premium 1", 184, "/ruta/base/cancion1");
    Cancion* cancion2 = new Cancion("123450102", "Hit Premium 2", 217, "/ruta/base/cancion2");
    Cancion* cancion3 = new Cancion("123450103", "Hit Premium 3", 195, "/ruta/base/cancion3");

    album->agregarCancion(cancion1);
    album->agregarCancion(cancion2);
    album->agregarCancion(cancion3);
    artista->agregarAlbum(album);

    UsuarioPremium* usuario1 = new UsuarioPremium("premium_user", "Medellín", "Colombia", "2024-01-01");
    UsuarioPremium* usuario2 = new UsuarioPremium("otro_premium", "Bogotá", "Colombia", "2024-02-01");

    cout << "=== INFORMACIÓN INICIAL ===" << endl;
    usuario1->mostrarInfo();

    cout << "\n=== REPRODUCCIONES PREMIUM ===" << endl;
    usuario1->reproducirCancion(cancion1, "/ruta/portada.png", "Artista Premium");
    usuario1->reproducirCancion(cancion2, "/ruta/portada.png", "Artista Premium");

    cout << "\n=== GESTIÓN DE FAVORITOS ===" << endl;
    usuario1->agregarFavorito(cancion1);
    usuario1->agregarFavorito(cancion2);
    usuario1->agregarFavorito(cancion1);

    usuario1->mostrarFavoritos();

    cout << "\n=== SEGUIR USUARIOS ===" << endl;
    usuario1->seguirUsuario(usuario2);
    usuario1->seguirUsuario(usuario2);
    usuario1->mostrarUsuariosSeguidos();

    cout << "\n=== OPCIONES PREMIUM ===" << endl;
    usuario1->mostrarOpcionesReproduccion();

    cout << "\n=== CANCIONES ANTERIORES ===" << endl;
    Cancion* anterior = usuario1->getCancionAnterior(1);
    if (anterior != nullptr) {
        cout << "Canción anterior: " << anterior->getNombre() << endl;
    }

    cout << "\n=== INFORMACIÓN FINAL ===" << endl;
    usuario1->mostrarInfo();

    cout << "\n=== RESUMEN ===" << endl;
    usuario1->mostrarResumen();
    cout << endl;

    delete usuario1;
    delete usuario2;
    delete artista;

    cout << "\n=== PRUEBA COMPLETADA ===" << endl;
    return 0;
}
