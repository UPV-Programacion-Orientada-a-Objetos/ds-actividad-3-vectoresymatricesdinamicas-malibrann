#include <iostream>

float** matrizProduccion;
int numProductos = 5;
int numSemanas = 4;

float* costosUnitarios;
float* inventarioMP;
int numMP = 4;

int requerimientos[5][4];
float costosMP[4];

void inicializarSistema() {
    matrizProduccion = new float*[numProductos];
    for(int i = 0; i < numProductos; i++) {
        matrizProduccion[i] = new float[numSemanas];
        for(int j = 0; j < numSemanas; j++) {
            matrizProduccion[i][j] = 0.0f;
        }
    }
    
    costosUnitarios = new float[numProductos];
    costosUnitarios[0] = 5.50f;
    costosUnitarios[1] = 7.25f;
    costosUnitarios[2] = 6.00f;
    costosUnitarios[3] = 8.50f;
    costosUnitarios[4] = 4.75f;
    
    inventarioMP = new float[numMP];
    inventarioMP[0] = 1000.0f;
    inventarioMP[1] = 800.0f;
    inventarioMP[2] = 1200.0f;
    inventarioMP[3] = 600.0f;
    
    costosMP[0] = 10.0f;
    costosMP[1] = 15.0f;
    costosMP[2] = 8.0f;
    costosMP[3] = 20.0f;
    
    int req[5][4] = {
        {2, 1, 0, 1},
        {1, 2, 1, 0},
        {3, 0, 2, 1},
        {0, 3, 1, 2},
        {1, 1, 1, 1}
    };
    
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 4; j++) {
            requerimientos[i][j] = req[i][j];
        }
    }
    
    float datos[5][4] = {
        {1000, 1200, 1100, 1300},
        {800, 900, 850, 950},
        {1500, 1600, 1550, 1700},
        {600, 700, 650, 750},
        {900, 1000, 950, 1050}
    };
    
    for(int i = 0; i < numProductos; i++) {
        for(int j = 0; j < numSemanas; j++) {
            matrizProduccion[i][j] = datos[i][j];
        }
    }
    
    std::cout << "\nsistema de Planificacion y Costos (COGS)\n";
    std::cout << "Inicializacion exitosa. Matriz de Planificacion: " 
         << numProductos << " Productos x " << numSemanas << " Semanas.\n";
}

void liberarMemoria() {
    for(int i = 0; i < numProductos; i++) {
        delete[] matrizProduccion[i];
    }
    delete[] matrizProduccion;
    
    delete[] costosUnitarios;
    delete[] inventarioMP;
    
    std::cout << "\nlibreando memoria \n";
}

void verPlanProduccion() {
    std::cout << "\nPlan de produccion\n";
    std::cout << "Producto     ";
    for(int j = 0; j < numSemanas; j++) {
        std::cout << "Sem" << j+1 << "     ";
    }
    std::cout << "\n";
    
    char nombres[5] = {'A', 'B', 'C', 'D', 'E'};
    for(int i = 0; i < numProductos; i++) {
        std::cout << "Prod " << nombres[i] << "      ";
        for(int j = 0; j < numSemanas; j++) {
            std::cout << matrizProduccion[i][j] << "   ";
        }
        std::cout << "\n";
    }
}

void agregarSemana() {
    std::cout << "\nAgregando semana " << numSemanas + 1 << "...\n";
    
    float** nuevaMatriz = new float*[numProductos];
    for(int i = 0; i < numProductos; i++) {
        nuevaMatriz[i] = new float[numSemanas + 1];
        
        for(int j = 0; j < numSemanas; j++) {
            nuevaMatriz[i][j] = matrizProduccion[i][j];
        }
        
        nuevaMatriz[i][numSemanas] = 0.0f;
    }
    
    for(int i = 0; i < numProductos; i++) {
        delete[] matrizProduccion[i];
    }
    delete[] matrizProduccion;
    
    matrizProduccion = nuevaMatriz;
    numSemanas++;
    
    std::cout << "Matriz redimensionada a " << numProductos << "x" << numSemanas 
         << ". Memoria gestionada con exito\n";
}

void modificarProduccion() {
    int producto, semana;
    float cantidad;
    
    std::cout << "\nIngrese Producto (0-" << numProductos-1 << "): ";
    std::cin >> producto;
    
    if(producto < 0 || producto >= numProductos) {
        std::cout << "Producto invalid\n";
        return;
    }
    
    std::cout << "Ingrese Semana (0-" << numSemanas-1 << "): ";
    std::cin >> semana;
    
    if(semana < 0 || semana >= numSemanas) {
        std::cout << "Semana invalida.\n";
        return;
    }
    
    std::cout << "Cantidad a producir: ";
    std::cin >> cantidad;
    
    matrizProduccion[producto][semana] = cantidad;
    std::cout << "Produccion actualizada exitosamente\n";
}

void calcularCOGS() {
    int semana;
    std::cout << "\nIngrese Semana para el calculo de costos (0-" << numSemanas-1 << "): ";
    std::cin >> semana;
    
    if(semana < 0 || semana >= numSemanas) {
        std::cout << "Semana invalida.\n";
        return;
    }
    
    float produccionTotal = 0.0f;
    float cogsTotal = 0.0f;
    
    for(int i = 0; i < numProductos; i++) {
        float unidades = matrizProduccion[i][semana];
        produccionTotal += unidades;
        cogsTotal += unidades * costosUnitarios[i];
    }
    
    float consumoMP[4] = {0, 0, 0, 0};
    for(int i = 0; i < numProductos; i++) {
        float unidades = matrizProduccion[i][semana];
        for(int mp = 0; mp < numMP; mp++) {
            consumoMP[mp] += unidades * requerimientos[i][mp];
        }
    }
    
    float valorInventarioFinal = 0.0f;
    for(int mp = 0; mp < numMP; mp++) {
        float inventarioRestante = inventarioMP[mp] - consumoMP[mp];
        if(inventarioRestante < 0) inventarioRestante = 0;
        valorInventarioFinal += inventarioRestante * costosMP[mp];
    }
    
    std::cout << "\n Reporte de Costos (Semana " << semana + 1 << ")\n";
    std::cout << "Produccion Total (Semana " << semana + 1 << "): " 
         << produccionTotal << " unidades.\n";
    std::cout << "Costo Total de Produccion (COGS): $" << cogsTotal << "\n";
    
    std::cout << "\nConsumo de Materia Prima:\n";
    for(int mp = 0; mp < numMP; mp++) {
        if(consumoMP[mp] > 0) {
            std::cout << "  MP-0" << mp+1 << ": " << consumoMP[mp] << " unidades\n";
        }
    }
    
    std::cout << "\nValor del Inventario Final (M.P. restante): $" 
         << valorInventarioFinal << "\n";
}

void mostrarMenu() {
    std::cout << "\nmenu\n";
    std::cout << "1. Ver Plan de Produccion\n";
    std::cout << "2. agregar neuva semana\n";
    std::cout << "3. Modificar Produccion\n";
    std::cout << "4. Calcular COGS y Final Inventory\n";
    std::cout << "5. Salir\n";
    std::cout << "\nOpcion seleccionada: ";
}

int main() {
    inicializarSistema();
    
    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;
        
        switch(opcion) {
            case 1:
                verPlanProduccion();
                break;
            case 2:
                agregarSemana();
                break;
            case 3:
                modificarProduccion();
                break;
            case 4:
                calcularCOGS();
                break;
            case 5:
                std::cout << "\nSaliendo del sistema...\n";
                break;
            default:
                std::cout << "Opcion invalida\n";
        }
    } while(opcion != 5);
    
    liberarMemoria();
    return 0;
}