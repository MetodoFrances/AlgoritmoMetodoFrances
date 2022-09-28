Funcion calcularPeriodoDePago(saldoInicial Por Referencia, saldoFinal Por Referencia, cuotaFija Por Referencia, period Por Referencia, tipoDeGracia Por Valor, porcentajeTEP, seguroRiesgo, comisionPeriodica, depreciacion, porcentajeImpuestoALaRenta, porcentajeIGV, totalCuotas, recompra)
	saldoInicial = saldoFinal
	interes <- saldoInicial * porcentajeTEP
	Si tipoDeGracia = 'P' Entonces
		cuotaFija <- interes
	Fin Si
	Si tipoDeGracia = 'T' Entonces
		cuotaFija <- 0.00
	Fin si
	
	Definir amortizacion como real
	
	Si tipoDeGracia = 'T' Entonces
		amortizacion <- 0.00
	SiNo
		amortizacion <- cuotaFija - interes
	Fin Si
	
	ahorroTributario <- (interes + seguroRiesgo + comisionPeriodica + depreciacion) * porcentajeImpuestoALaRenta
	Definir recompraP como real
	Si period = totalCuotas Entonces
		recompraP <- recompra
	SiNo
		recompraP <- 0.00
	Fin Si
	igvCuota <- (cuotaFija + seguroRiesgo + comisionPeriodica + recompraP)*porcentajeIGV
	flujoBruto <- cuotaFija + seguroRiesgo + comisionPeriodica + recompraP
	flujoConIGV <- flujoBruto + igvCuota
	flujoNeto <- flujoBruto - ahorroTributario
	flujoTCEA = cuotaFija
	Si tipoDeGracia = 'T' Entonces
		saldoFinal <- saldoInicial + interes
	SiNo
		saldoFinal <- saldoInicial - amortizacion
	Fin Si
	Si saldoFinal < 1.00 Entonces
		saldoFinal <- 0.00
	Fin Si
	Escribir  saldoInicial, " ", interes, " ", cuotaFija, " ", amortizacion, " ", seguroRiesgo, " ", comisionPeriodica, " ", recompraP, " ", saldoFinal, " ", depreciacion, " ", ahorroTributario, " ", igvCuota, " ", flujoBruto, " ", flujoConIGV, " ", flujoNeto, " ", flujoTCEA
	
	Si tipoDeGracia = 'T' o tipoDeGracia = 'P' Entonces
		cuotasRestantes <- totalCuotas - period
		cuotaFija <- (saldoFinal * porcentajeTEP) / (1 - (1 + porcentajeTEP)^(cuotasRestantes * (-1)))
	Fin Si
	
Fin Funcion

Funcion validarTipoDeGracia(saldoInicial Por Referencia, saldoFinal Por Referencia, cuotaFija Por Referencia, period Por Referencia,porcentajeTEP, seguroRiesgo, comisionPeriodica, depreciacion, porcentajeImpuestoALaRenta, porcentajeIGV, totalCuotas, recompra)
	Definir tipoDeGracia Como Caracter
	Escribir "Ingrese plazo de Gracia: (S: Sin plazo de gracia, P: parcial, T: total): "
	Leer tipoDeGracia
	Definir n como numero
	Si tipoDeGracia = 'P' Entonces
		Escribir "Ingresa cantidad de plazos de gracia parcial: "
		Leer n
		Para i<-0 Hasta n Con Paso 1 Hacer
			calcularPeriodoDePago(saldoInicial,saldoFinal,cuotaFija,period,tipoDeGracia,porcentajeTEP, seguroRiesgo, comisionPeriodica, depreciacion, porcentajeImpuestoALaRenta, porcentajeIGV, totalCuotas, recompra)
			period = period + 1
		Fin Para
	SiNo
		Si tipoDeGracia = 'T' Entonces
			Escribir "Ingresa cantidad de plazos de gracia total: "
			Leer n
			Para i<-0 Hasta n Con Paso 1 Hacer
				calcularPeriodoDePago(saldoInicial,saldoFinal,cuotaFija,period,tipoDeGracia,porcentajeTEP, seguroRiesgo, comisionPeriodica, depreciacion, porcentajeImpuestoALaRenta, porcentajeIGV, totalCuotas, recompra)
				period = period + 1
			Fin Para
		Fin Si
	Fin Si
Fin Funcion

Funcion IngresarDatosDelPrestamo ( precioDeVentaDelActivo por Referencia, anios por Referencia, frecuenciaDePagoDias Por Referencia, porcentajeTEA Por Referencia, porcentajeRecompra Por Referencia)
	Escribir "Ingresar precio de venta del activo: "
	Leer precioDeVentaDelActivo
	Escribir "Ingresar cantidad en anios de duración del prestamo: "
	Leer anios
	Repetir
		Escribir "Ingresar frecuencia de pago:  180 = Semestral, 90 = Trimestral, 30 = Mensual, 360 = Anual, 120 = Cuatrimestral"
		Leer frecuenciaDePagoDias
	Hasta Que (frecuenciaDePagoDias = 120 o frecuenciaDePagoDias = 90 o frecuenciaDePagoDias = 30 o frecuenciaDePagoDias = 360 o frecuenciaDePagoDias = 120)
	
	Definir opcionT Como Caracter
	Escribir "Ingrese tasa nominal o tasa efectiva anual: N = nominal, E = efectiva"
	Leer opcionT
	
	Si opcionT = 'E' Entonces
		Escribir "Ingrese TEA: "
		Leer porcentajeTEA
	SiNo
		Definir porcentajeTNA como real
		Escribir "Ingrese TNA: "
		Leer porcentajeTNA
		porcentajeTEA <- ((1 + (porcentajeTNA / 360.00))^360.00) - 1
	Fin Si
	
	Escribir "Ingrese porcentaje de recompra: "
	Leer porcentajeRecompra
	
	Escribir "Mi frecuencia de pago dias ", frecuenciaDePagoDias
	
Fin Funcion

Funcion IngresarCostosAdicionales (costesRegistrales Por Referencia, costesNotariales Por Referencia, tasacion Por Referencia, comisionDeEstudio Por Referencia, comisionDeActivacion Por Referencia, comisionPeriodica Por Referencia, porcentajeDeSeguroRiesgo Por Referencia)
	Escribir "Ingrese costes registrales: "
	Leer costesRegistrales
	Escribir "Ingrese costes notariales: "
	Leer costesNotariales
	Escribir "Ingrese tasacion: "
	Leer tasacion
	Escribir "Ingrese comision de estudio: "
	Leer comisionDeEstudio
	Escribir "Ingrese comision de activacion: "
	Leer comisionDeActivacion
	Escribir "Ingrese comision periodica: "
	Leer comisionPeriodica
	Escribir "Ingrese porcentaje de seguro contra riesgo: "
	Leer porcentajeDeSeguroRiesgo
Fin Funcion




Algoritmo metodoFrances
	Definir precioDeVentaDelActivo como real
	Definir valorVentaDelActivo como real
	Definir anios como real
	Definir porcentajeTN como real
	Definir porcentajeTEA como real
	porcentajeIGV <- 0.18
	porcentajeImpuestoALaRenta <- 0.30
	Definir porcentajeRecompra como real
	Definir porcentajeTEP como real
	
	Definir costesRegistrales como real
	Definir costesNotariales como real
	Definir comisionDeEstudio como real
	Definir comisionDeActivacion como real
	Definir comisionPeriodica como real
	Definir frecuenciaDePagoDias como real
	
	IngresarCostosAdicionales(costesNotariales,costesRegistrales,tasacion,comisionDeEstudio,comisionDeActivacion,comisionPeriodica,porcentajeDeSeguroRiesgo)
	IngresarDatosDelPrestamo(precioDeVentaDelActivo,anios,frecuenciaDePagoDias,porcentajeTEA,porcentajeRecompra)
	tasaDeDescuentoKs <- 0.1750
    tasaDeDescuentoWACC <- 0.10
	
	Definir montoDelLeasing como Real
    TEA <- 0.00
    Definir totalCuotas como Real
    Definir cuotasPorAnio como Real
    diasPorAnio <- 360.00
    
	
	Definir cuotasGraciaParcial como Real
    Definir cuotasGraciaTotal como Real
	
    Definir IGV como real
    Definir seguroRiesgo como real
	Definir depreciacion como Real
	Definir recompra como Real
	
	cuotasPorAnio <- 360.00 / frecuenciaDePagoDias
	totalCuotas <- cuotasPorAnio * anios
	IGV = (precioDeVentaDelActivo / (1.00 + porcentajeIGV))*porcentajeIGV
	valorVentaDelActivo <- precioDeVentaDelActivo - IGV
	porcentajeTEP <- (1 + porcentajeTEA)^(frecuenciaDePagoDias / diasPorAnio) - 1.00
	seguroRiesgo <- (porcentajeSeguroRiesgo * precioDeVentaDelActivo) / cuotasPorAnio
	montoDelLeasing <- valorVentaDelActivo + costesNotariales + costesRegistrales + tasacion + comisionDeEstudio + comisionDeActivacion
	depreciacion <- valorVentaDelActivo / totalCuotas
	recompra <- valorVentaDelActivo * porcentajeRecompra
	
	cuotaFija <- (montoDelLeasing * porcentajeTEP) / (1 - (1 + porcentajeTEP)^(totalCuotas*(-1)))
	saldoInicial <- montoDelLeasing
	saldoFinal <- montoDelLeasing
	period <- 1
	
	Escribir "Saldo inicial Interes Cuota Amortizacion SeguroRiesgo Recompra SaldoFinal AhorroTributario IGV FlujoBruto FlujoConIGV FlujoNeto FlujoTCEA"
	Escribir "0 - - - - - - - - - -", saldoInicial
	
	validarTipoDeGracia(saldoInicial,saldoFinal,cuotaFija,period,porcentajeTEP, seguroRiesgo, comisionPeriodica, depreciacion, porcentajeImpuestoALaRenta, porcentajeIGV, totalCuotas, recompra)
	c <- 'S'
	Mientras period <= totalCuotas Hacer
		calcularPeriodoDePago(saldoInicial,saldoFinal,cuotaFija,period,c,porcentajeTEP, seguroRiesgo, comisionPeriodica, depreciacion, porcentajeImpuestoALaRenta, porcentajeIGV, totalCuotas, recompra)
		period <- period + 1
	Fin Mientras
	
FinAlgoritmo
