# 1. Nodo Bluetooth: Cálculo de Batería y Alimentación

Este nodo, que controla una bomba de agua, consume alrededor de **397.62 mA** cuando está en uso. Aquí vamos a ver cómo elegir la batería adecuada y calcular la alimentación solar o por red eléctrica.

## Cálculo de la batería
Para saber cuánto dura la batería con este consumo, usamos esta fórmula sencilla:

Duración (horas) = Capacidad de la batería (mAh) / Consumo del nodo (mA)


### Ejemplos de duración para baterías comunes:

- **Batería de 1000 mAh** (LiPo 3.7V):

1000 mAh / 397.62 mA ≈ 2.51 horas

- **Batería de 3000 mAh** (LiPo 3.7V):

3000 mAh / 397.62 mA ≈ 7.54 horas

- **Batería de 5000 mAh** (LiPo 3.7V):

5000 mAh / 397.62 mA ≈ 12.58 horas


## Panel Solar y Cálculo de Carga
Ahora, si piensas en energía solar, necesitas un panel que alimente el nodo **de día** y cargue la batería **para la noche**. Aquí te explico cómo calcular la potencia del panel.

Para calcular cuánta energía solar necesitas, usamos esta fórmula:

Potencia del panel (W) = Consumo del nodo (W) / Horas de luz solar efectiva (h)


Primero, convertimos el consumo del nodo a vatios:

Consumo (W) = (397.62 mA * 3.7V) / 1000 ≈ 1.47 W

Si suponemos que hay **5 horas de luz solar efectiva** al día:

1.47 W / 5 h ≈ 0.29 W

Esto significa que un **panel solar de 6V 1W** sería suficiente para alimentar el nodo y cargar una batería de hasta 3000 mAh. ¡Perfecto para un sistema autónomo!

## Alimentación Alterna (CA)
Si en vez de depender del sol, quieres conectar el nodo a la corriente eléctrica, solo necesitas una fuente de alimentación sencilla. Para este nodo Bluetooth:

- **Voltaje:** 5V
- **Corriente:** 1A - 2A (para los picos cuando la bomba se enciende)

Recomendación: Un cargador USB de **5V 2A** sería ideal para este nodo.

# 2. Nodo LoRa: Cálculo de Batería y Alimentación

Este nodo tiene un consumo un poquito más alto que el de Bluetooth, **477.62 mA**, ya que LoRa es para distancias largas. Vamos a repetir los cálculos para batería y energía solar, pero adaptados a este mayor consumo.

## Cálculo de la batería

- **Batería de 1000 mAh** (LiPo 3.7V):

1000 mAh / 477.62 mA ≈ 2.09 horas

- **Batería de 3000 mAh** (LiPo 3.7V):

3000 mAh / 477.62 mA ≈ 6.28 horas

- **Batería de 5000 mAh** (LiPo 3.7V):
5000 mAh / 477.62 mA ≈ 10.47 horas


## Panel Solar y Cálculo de Carga
Para la parte solar, seguimos el mismo proceso que antes. Primero, el consumo en vatios:

Consumo (W) = (477.62 mA * 3.7V) / 1000 ≈ 1.77 W


Con **5 horas de luz solar efectiva**:

1.77 W / 5 h ≈ 0.35 W


Aquí, un **panel solar de 6V 2W** sería suficiente para mantener el nodo funcionando y cargar la batería durante el día.

## Alimentación Alterna (CA)
Si vas a conectar el nodo a la corriente alterna, necesitas una fuente un poco más potente que la del nodo Bluetooth, ya que el consumo es mayor:

- **Voltaje:** 5V
- **Corriente:** 2A - 3A (para los picos de la bomba y la transmisión de LoRa)

Un adaptador de **5V 3A** funcionaría perfecto para alimentar el nodo LoRa.

# 3. Sistema de Alimentación de los Nodos con Batería y Panel Solar

Aquí va un resumen para que elijas bien:

## Selección de baterías:
- **Nodo Bluetooth:** Una batería entre **1000 mAh y 3000 mAh** estaría bien, dependiendo de cuántas horas necesites que funcione.
- **Nodo LoRa:** Necesitarás una batería más grande, entre **3000 mAh y 5000 mAh**, ya que el consumo es más alto.

## Controlador de Carga Solar:
Ambos nodos necesitan un **controlador de carga solar** para proteger la batería y optimizar el uso de energía del panel. Un controlador de **3.7V a 5V** que soporte paneles de entre 1W y 2W sería lo ideal.

## Alimentación por CA:
Si vas a usar corriente alterna (o sea, conectar a la pared):

- **Nodo Bluetooth:** Con un adaptador de **5V 2A** te alcanza.
- **Nodo LoRa:** Mejor usa un adaptador de **5V 3A**, ya que el nodo consume más.

# 4. Aplicación del Sistema en un Riego Vertical

Si pensamos en un **sistema de riego vertical**, la idea es usar estos nodos para controlar el riego de plantas en diferentes niveles de la estructura. La comunicación dependerá de la distancia:

- **Nodo Bluetooth:** Perfecto para distancias cortas, como en un jardín vertical dentro de una casa o edificio.
- **Nodo LoRa:** Ideal para áreas rurales o grandes terrenos donde el control central está a varios kilómetros de distancia.

Ambos nodos pueden funcionar de manera autónoma con energía solar y baterías recargables, lo que es genial si el sistema está en un lugar sin acceso a la red eléctrica.


- **Nodos Bluetooth:** Para distancias cortas y bajo consumo, una batería de entre **1000 mAh y 3000 mAh** y un panel solar de **6V 1W** mantendrán todo funcionando durante varias horas.
- **Nodos LoRa:** Para distancias largas y mayor consumo, necesitas una batería de entre **3000 mAh y 5000 mAh** y un panel solar de **6V 2W** para asegurar que el nodo siga activo durante el día y la noche.

Ambos sistemas pueden conectarse fácilmente a la corriente con adaptadores de **5V 2A (Bluetooth)** y **5V 3A (LoRa)**. Y si decides usar paneles solares, el controlador de carga es un componente esencial para que todo funcione sin problemas.
