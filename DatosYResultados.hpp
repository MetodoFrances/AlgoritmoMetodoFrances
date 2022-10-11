#ifndef __DATOS_Y_RESULTADOS__
#define __DATOS_Y_RESULTADOS__

namespace DatosIniciales {
    
    struct CostesIniciales {
        double costesRegistrales;
        double costesNotariales;
        double tasacion;
        double comisionDeEstudio;
        double comisionDeActivacion;
    };

    struct DatosDelPrestamo {
        double precioVentaDelActivo;
        double anios;
        double frecuenciaDePagoDias;
        double diasPorAnio = 360.00;
        double porcentajeTEA;
        double porcentajeIGV = 0.18;
        double porcentajeImpuestoALaRenta;
        double porcentajeRecompra;
        double porcentajeTN;
        double ValorVentaDelActivo;
    };

    struct CostesPeriodicos {
        double comisionPeriodica;
        double porcentajeDeSeguroRiesgo;
    };

    struct CostesDeOportunidad {
        double tasaDeDescuentoKs;
        double tasaDeDescuentoWACC;
    };
}

namespace ResultadosDelLeasing {
    struct ResultadosDelArrendamiento {
        int TIR;
    };
}

#endif