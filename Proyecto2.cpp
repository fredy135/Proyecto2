#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

struct producto {
    string nombre;
    string codigo;
    double precio;
    string proveedor;
    int existencia;
    char estado; // A = aprobado y R = reprobado
    double descuento;
};

int main() {
    fstream productFile("productos.txt", ios::in | ios::out | ios::app);

    if (!productFile.is_open()) {
        cerr << "No se pudo abrir el archivo 'productos.txt'" << endl;
        return 1;
    }

    int opciones;
    do {
        cout << "1. Mostrar productos:" << endl;
        cout << "2. Agregar producto:" << endl;
        cout << "3. Modificar producto: " << endl;
        cout << "4. Salir" << endl;
        cout << "Elija una opcion: ";
        cin >> opciones;

        switch (opciones) {
            case 1: {
                cout << "Productos en el archivo: " << endl;
                producto product;
                productFile.clear();
                productFile.seekg(0, ios::beg);
                while (productFile >> product.nombre >> product.codigo >> product.precio >> product.proveedor >> product.existencia >> product.estado >> product.descuento) {
                    cout << "Nombre: " << product.nombre << ", Codigo: " << product.codigo << ", Precio: " << product.precio << ", Proveedor: " << product.proveedor << ", Existencia: " << product.existencia << ", Estado: " << product.estado << ", Descuento: " << product.descuento<< '%'<< endl;
                }
                break;
            }
            case 2: {
                producto newProduct;
                producto existingProduct;
                cout << "Ingrese los datos del nuevo producto:" << endl;
                cout << "Nombre: ";
                cin >> newProduct.nombre;
                cout << "Codigo: ";
                cin >> newProduct.codigo;

                // Verificar si el código existe
                bool codigoExistente = false;
                productFile.clear();
                productFile.seekg(0, ios::beg);
                while (productFile >> existingProduct.nombre >> existingProduct.codigo >> existingProduct.precio >> existingProduct.proveedor >> existingProduct.existencia >> existingProduct.estado >> existingProduct.descuento) {
                    if (existingProduct.codigo == newProduct.codigo) {
                        codigoExistente = true;
                        break;
                    }
                }

                if (codigoExistente) {
                    cout << "Ya existe un producto con el mismo codigo. Ingrese un codigo que no exista aun " << endl;
                } else {
                    cout << "Precio: ";
                    cin >> newProduct.precio;
                    cout << "Proveedor: ";
                    cin >> newProduct.proveedor;
                    cout << "Existencia: ";
                    cin >> newProduct.existencia;
                    cout << "Estado (A/R): ";
                    cin >> newProduct.estado;
                    cout << "Descuento: ";
                    cin >> newProduct.descuento;

                    productFile.clear();
                    productFile.seekp(0, ios::end);

                    // Guarda el producto en el archivo
                    productFile << newProduct.nombre << " " << newProduct.codigo << " " << newProduct.precio << " " << newProduct.proveedor << " " << newProduct.existencia << " " << newProduct.estado << " " << newProduct.descuento << endl;
                }
                break;
            }
            case 3: {
                string codigoModificar;
                cout << "Ingrese el codigo del producto que quiera modificar: ";
                cin >> codigoModificar;

                bool productoEncontrado = false;
                productFile.clear();
                productFile.seekp(0, ios::beg);

                fstream tempFile("temp.txt", ios::out | ios::in);

                if (!tempFile.is_open()) {
                    cerr << "No existe ese codigo." << endl;
                    return 1;
                }

                producto existingProduct;
                while (productFile >> existingProduct.nombre >> existingProduct.codigo >> existingProduct.precio >> existingProduct.proveedor >> existingProduct.existencia >> existingProduct.estado >> existingProduct.descuento) {
                    if (existingProduct.codigo == codigoModificar) {
                        productoEncontrado = true;
                        cout << "Ingrese los nuevos datos para el producto:" << endl;
                        cout << "Nombre: ";
                        cin >> existingProduct.nombre;
                        cout << "Precio: ";
                        cin >> existingProduct.precio;
                        cout << "Proveedor: ";
                        cin >> existingProduct.proveedor;
                        cout << "Existencia: ";
                        cin >> existingProduct.existencia;
                        cout << "Estado (A/R): ";
                        cin >> existingProduct.estado;
                        cout << "Descuento: ";
                        cin >> existingProduct.descuento;
                    }
                    // Guarda los datos en un archivo temporal
                    tempFile << existingProduct.nombre << " " << existingProduct.codigo << " " << existingProduct.precio << " " << existingProduct.proveedor << " " << existingProduct.existencia << " " << existingProduct.estado << " " << existingProduct.descuento << endl;
                }

                if (!productoEncontrado) {
                    cout << "Producto no encontrado." << endl;
                }

                // Cierra el archivo original
                productFile.close();
                tempFile.close();

                // Elimina el archivo original
                remove("productos.txt");

                // Renombra el archivo temporal al archivo original
                rename("temp.txt", "productos.txt");

                // Reabre el archivo original para continuar con otras operaciones
                productFile.open("productos.txt", ios::in | ios::out | ios::app);
                break;
            }
            case 4:
                break;
            default:
                cout << "Opción no valida. Elija una opcion valida." << endl;
                break;
        }
    } while (opciones != 4);

    productFile.close();

    return 0;
}

