# Practicas Webots

Repositorio con las 4 practicas de Webots (Tutorial 1, Tutorial 6, Helicoptero y Pendulo con PID manual).

## Practicas

1. **E-puck - usar un robot y girar una llanta - Tutorial 1 Webots**
   Mundo: `worlds/01_epuck.wbt`
   Controlador: `controllers/avanzador/avanzador.cpp`

2. **Disenar carrito - Tutorial 6 Webots**
   Mundo: `worlds/02_carrito.wbt`
   Practica de modelado (4 ruedas via HingeJoint + body). No lleva controlador,
   Tutorial 6 es sobre construir la geometria del robot, no moverlo.

3. **Helicoptero**
   Mundo: `worlds/03_helicoptero.wbt`
   Controlador: `controllers/Velocidad_constante/Velocidad_constante.cpp`

4. **Pendulo - PID Manual**
   Mundo: `worlds/04_pendulo.wbt`
   Controlador: `controllers/pendulo_pid/pendulo_pid.cpp`

## Como abrir cada practica

1. Abre Webots.
2. File > Open World... y selecciona el `.wbt` de la tabla de arriba.
3. Webots compila y corre automaticamente el controlador indicado en el nodo `Robot > controller`.

## Practica 4 - Pendulo (PID manual)

`controllers/pendulo_pid/pendulo_pid.cpp` implementa un PID clasico
(`u = Kp*e + Ki*integral(e) + Kd*d(e)/dt`) escrito a mano (no usa el PID
integrado de Webots `setControlPID`). El motor se controla en modo torque
(`setPosition(INFINITY)` + `setTorque(u)`) para sostener el pendulo en un
angulo objetivo (`setpoint = -1.0` rad).

Si oscila mucho o tarda en estabilizarse, ajusta `Kp`, `Ki`, `Kd` al inicio
del archivo.

## Estructura

```text
controllers/
  avanzador/
  Velocidad_constante/
  pendulo_pid/
worlds/
  01_epuck.wbt
  02_carrito.wbt
  03_helicoptero.wbt
  04_pendulo.wbt
```
