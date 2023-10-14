import os

class Producto:
    def __init__(self, nombre, codigo, precio, proveedor, existencia, estado, descuento):
        self.nombre = nombre
        self.codigo = codigo
        self.precio = precio
        self.proveedor = proveedor
        self.existencia = existencia
        self.estado = estado
        self.descuento = descuento

def main():
    opciones = 0
    productFile = open("productos.txt", "a+")

    if not productFile:
        print("No se pudo abrir el archivo 'productos.txt'")
        return

    while opciones != 4:
        print("1. Mostrar productos:")
        print("2. Agregar producto:")
        print("3. Modificar producto:")
        print("4. Salir")
        opciones = int(input("Elija una opción: "))

        if opciones == 1:
            print("Productos en el archivo:")
            productFile.seek(0)
            for line in productFile:
                product_data = line.split()
                nombre, codigo, precio, proveedor, existencia, estado, descuento = product_data
                print(f"Nombre: {nombre}, Codigo: {codigo}, Precio: {precio}, Proveedor: {proveedor}, Existencia: {existencia}, Estado: {estado}, Descuento: {descuento}%")

        elif opciones == 2:
            codigoExistente = False
            newProduct = Producto(
                input("Nombre: "),
                input("Codigo: "),
                float(input("Precio: ")),
                input("Proveedor: "),
                int(input("Existencia: ")),
                input("Estado (A/R): "),
                float(input("Descuento: "))
            )

            productFile.seek(0)
            for line in productFile:
                existingProduct = Producto(*line.split())
                if existingProduct.codigo == newProduct.codigo:
                    codigoExistente = True
                    break

            if codigoExistente:
                print("Ya existe un producto con el mismo código. Ingrese un código que no exista aún.")
            else:
                productFile.write(f"{newProduct.nombre} {newProduct.codigo} {newProduct.precio} {newProduct.proveedor} {newProduct.existencia} {newProduct.estado} {newProduct.descuento}\n")

        elif opciones == 3:
            codigoModificar = input("Ingrese el código del producto que quiera modificar: ")
            productoEncontrado = False

            productFile.seek(0)
            lines = productFile.readlines()
            productFile.close()

            tempFile = open("temp.txt", "w+")

            for line in lines:
                existingProduct = Producto(*line.split())
                if existingProduct.codigo == codigoModificar:
                    productoEncontrado = True
                    print("Ingrese los nuevos datos para el producto:")
                    existingProduct.nombre = input("Nombre: ")
                    existingProduct.precio = float(input("Precio: "))
                    existingProduct.proveedor = input("Proveedor: ")
                    existingProduct.existencia = int(input("Existencia: "))
                    existingProduct.estado = input("Estado (A/R): ")
                    existingProduct.descuento = float(input("Descuento: "))
                tempFile.write(f"{existingProduct.nombre} {existingProduct.codigo} {existingProduct.precio} {existingProduct.proveedor} {existingProduct.existencia} {existingProduct.estado} {existingProduct.descuento}\n")

            tempFile.close()

            os.remove("productos.txt")
            os.rename("temp.txt", "productos.txt")

            productFile = open("productos.txt", "a+")

        elif opciones == 4:
            break

        else:
            print("Opción no válida. Elija una opción válida.")

    productFile.close()

if __name__ == "__main__":
    main()
