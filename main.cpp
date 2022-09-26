#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include "DatosYResultados.hpp"

using std::cout;
using std::cin;
using namespace DatosIniciales;
using namespace ResultadosDelLeasing;

class LeasingFrances {
public:
    LeasingFrances() {
        costesIniciales = {250.00 , 150.00 , 80.00 , 100.00, 50.00};
        costesPeriodicos = {10.00, 0.0030};
        costesDeOportunidad = {0.1750, 0.10};
    }
    void cronogramaDePagos() {
        _entradaDeDatos();
        _calculosIntermedios();
        _mostrarDatosDelPrestamo();
        double cuotaFija = (montoDelLeasing * porcentajeTEP) / (1 - pow(1 + porcentajeTEP, totalCuotas * (-1)));
        double saldoInicial = montoDelLeasing;
        double saldoFinal = montoDelLeasing;
        uint64_t period = 1;
        cout << "\n  Saldo inicial Interes Cuota Amortizacion SeguroRiesgo Recompra SaldoFinal AhorroTributario IGV FlujoBruto FlujoConIGV FlujoNeto FlujoTCEA";
        cout << "\n0 - - - - - - - - - - " << saldoInicial;
        _validarTipoDeGracia(saldoInicial,saldoFinal,cuotaFija,period);
        for (period; period <= totalCuotas; ++period)
           _calcularPeriodoDePagoSinGracia(saldoInicial,saldoFinal,cuotaFija,period);
    }
private:
    CostesIniciales costesIniciales;
    DatosDelPrestamo datosDelPrestamo;
    CostesPeriodicos costesPeriodicos;
    CostesDeOportunidad costesDeOportunidad;

    double porcentajeTEP;
    double montoDelLeasing;
    double totalCuotas;
    double cuotasPorAnio;
    double diasPorAnio = 360.00;
    double IGV;
    double seguroRiesgo;
    double depreciacion;
    double recompra;
private:
    void _entradaDeDatos() {
        cout << "\nIngrese precio de venta del activo: ";
        cin >> datosDelPrestamo.precioVentaDelActivo;
        cout << "\nIngrese anios: ";
        cin >> datosDelPrestamo.anios;
        cout << "\nIngrese frecuencia de pago (Dias): ";
        cin >> datosDelPrestamo.frecuenciaDePagoDias;
        cout << "\nIngrese porcentaje TEA: ";
        cin >> datosDelPrestamo.porcentajeTEA;
        cout << "\nIngrese porcentaje de Impuesto a la renta: ";
        cin >> datosDelPrestamo.porcentajeImpuestoALaRenta;
        cout << "\nIngrese porcentaje de recompra: ";
        cin >> datosDelPrestamo.porcentajeRecompra;
    }
    void _calculosIntermedios() {
        cuotasPorAnio = 360.00 / datosDelPrestamo.frecuenciaDePagoDias;
        totalCuotas = cuotasPorAnio * datosDelPrestamo.anios;
        IGV = (datosDelPrestamo.precioVentaDelActivo / (1.00 + datosDelPrestamo.porcentajeIGV)) * datosDelPrestamo.porcentajeIGV;
        datosDelPrestamo.ValorVentaDelActivo = datosDelPrestamo.precioVentaDelActivo - IGV;
        porcentajeTEP = pow(1 + datosDelPrestamo.porcentajeTEA,(datosDelPrestamo.frecuenciaDePagoDias / diasPorAnio)) - 1;
        seguroRiesgo = (costesPeriodicos.porcentajeDeSeguroRiesgo * datosDelPrestamo.precioVentaDelActivo) / cuotasPorAnio;
        montoDelLeasing = datosDelPrestamo.ValorVentaDelActivo + costesIniciales.costesNotariales + costesIniciales.costesRegistrales + costesIniciales.tasacion + costesIniciales.comisionDeEstudio + costesIniciales.comisionDeActivacion;
        depreciacion = datosDelPrestamo.ValorVentaDelActivo / totalCuotas;
        recompra = datosDelPrestamo.ValorVentaDelActivo * datosDelPrestamo.porcentajeRecompra;
    }
    void _mostrarDatosDelPrestamo() {
        // Ignoren esto, me puse creisi xd
        cout << "PV Anios Frec DiasXAnio %TEA %IGV %IR %REC\n";
        double* it = (double*)&datosDelPrestamo;
        for(size_t i = 0; i < 8; ++i, ++it) cout << *it << "  ";
        cout <<  "\n\n";
    }
    void _calcularPeriodoDePagoSinGracia(double& saldoInicial, double& saldoFinal, double& cuotaFija, uint64_t period) {
        saldoInicial = saldoFinal;
        double interes = saldoInicial * porcentajeTEP;
        double amortizacion = cuotaFija - interes;
        double ahorroTributario = (interes + seguroRiesgo + costesPeriodicos.comisionPeriodica + depreciacion) * datosDelPrestamo.porcentajeImpuestoALaRenta;
        double Recompra = ((period == totalCuotas)? recompra: 0);
        double igvCuota = (cuotaFija + seguroRiesgo + costesPeriodicos.comisionPeriodica + Recompra) * datosDelPrestamo.porcentajeIGV;
        double flujoBruto = cuotaFija + seguroRiesgo + costesPeriodicos.comisionPeriodica + Recompra;
        double flujoConIGV = flujoBruto + igvCuota;
        double flujoNeto = flujoBruto - ahorroTributario;
        double flujoTCEA = cuotaFija;
        saldoFinal = saldoInicial - amortizacion;
        if(saldoFinal < 1.00) saldoFinal = 0;
        cout << "\n" << saldoInicial << " " << interes << " " << cuotaFija << " " << amortizacion << " " << 
        seguroRiesgo << " " << costesPeriodicos.comisionPeriodica << " " << Recompra << " " << saldoFinal << " " << 
        depreciacion << " " << ahorroTributario << " " << igvCuota << " " << flujoBruto << " " <<
        flujoConIGV << " " << flujoNeto << " " << flujoTCEA;
    }
    void _calcularPeriodoDePagoConGraciaParcial(double& saldoInicial, double& saldoFinal, double& cuotaFija, uint64_t period) {
        saldoInicial = saldoFinal;
        double interes = saldoInicial * porcentajeTEP;
        cuotaFija = interes;
        double amortizacion = cuotaFija - interes; // 0
        double ahorroTributario = (interes + seguroRiesgo + costesPeriodicos.comisionPeriodica + depreciacion) * datosDelPrestamo.porcentajeImpuestoALaRenta;
        double Recompra = ((period == totalCuotas)? recompra: 0);
        double igvCuota = (cuotaFija + seguroRiesgo + costesPeriodicos.comisionPeriodica + Recompra) * datosDelPrestamo.porcentajeIGV;
        double flujoBruto = cuotaFija + seguroRiesgo + costesPeriodicos.comisionPeriodica + Recompra;
        double flujoConIGV = flujoBruto + igvCuota;
        double flujoNeto = flujoBruto - ahorroTributario;
        double flujoTCEA = cuotaFija;
        saldoFinal = saldoInicial - amortizacion;
        if(saldoFinal < 1.00) saldoFinal = 0;
        cout << "\n" << saldoInicial << " " << interes << " " << cuotaFija << " " << amortizacion << " " << 
        seguroRiesgo << " " << costesPeriodicos.comisionPeriodica << " " << Recompra << " " << saldoFinal << " " << 
        depreciacion << " " << ahorroTributario << " " << igvCuota << " " << flujoBruto << " " <<
        flujoConIGV << " " << flujoNeto << " " << flujoTCEA;
        double cuotasRestantes = totalCuotas - period;
        cuotaFija = (saldoFinal * porcentajeTEP) / (1 - pow(1 + porcentajeTEP, cuotasRestantes * (-1)));
    }
    void _calcularPeriodoDePagoConGraciaTotal(double& saldoInicial, double& saldoFinal, double& cuotaFija, uint64_t period) {
        saldoInicial = saldoFinal;
        double interes = saldoInicial * porcentajeTEP;
        cuotaFija = 0.00;
        double amortizacion = 0.00;
        double ahorroTributario = (interes + seguroRiesgo + costesPeriodicos.comisionPeriodica + depreciacion) * datosDelPrestamo.porcentajeImpuestoALaRenta;
        double Recompra = ((period == totalCuotas)? recompra: 0);
        double igvCuota = (cuotaFija + seguroRiesgo + costesPeriodicos.comisionPeriodica + Recompra) * datosDelPrestamo.porcentajeIGV;
        double flujoBruto = cuotaFija + seguroRiesgo + costesPeriodicos.comisionPeriodica + Recompra;
        double flujoConIGV = flujoBruto + igvCuota;
        double flujoNeto = flujoBruto - ahorroTributario;
        double flujoTCEA = cuotaFija;
        saldoFinal = saldoInicial + interes;
        if(saldoFinal < 1.00) saldoFinal = 0;
        cout << "\n" << saldoInicial << " " << interes << " " << cuotaFija << " " << amortizacion << " " << 
        seguroRiesgo << " " << costesPeriodicos.comisionPeriodica << " " << Recompra << " " << saldoFinal << " " << 
        depreciacion << " " << ahorroTributario << " " << igvCuota << " " << flujoBruto << " " <<
        flujoConIGV << " " << flujoNeto << " " << flujoTCEA;
        double cuotasRestantes = totalCuotas - period;
        cuotaFija = (saldoFinal * porcentajeTEP) / (1 - pow(1 + porcentajeTEP, cuotasRestantes * (-1)));
    }

    void _validarTipoDeGracia(double& saldoInicial, double& saldoFinal, double& cuotaFija, uint64_t& period) {
        char tipoGracia;
        cout << "\nIngrese plazo de Gracia: ('S': Sin plazo de gracia, 'P': parcial, 'T': total): ";
        cin >> tipoGracia;
        uint64_t n;
        switch (tipoGracia)
        {
        case 'P':
            cout << "\nIngresa cantidad de plazos de gracia parcial: ";
            cin >> n;
            for(period; period <= n; ++period)
                _calcularPeriodoDePagoConGraciaParcial(saldoInicial,saldoFinal,cuotaFija,period);
            break;
        case 'T':
            cout << "\nIngresa cantidad de plazos de gracia parcial: ";
            cin >> n;
            for(period; period <= n; ++period)
                _calcularPeriodoDePagoConGraciaTotal(saldoInicial,saldoFinal,cuotaFija,period);
            break;
        }
    }
};

int main() {
    LeasingFrances lf;
    lf.cronogramaDePagos();
    return 0;
}