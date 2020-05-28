# Sistema-Operativos

Por turno ciclico:
El funcionamiento de mi programa de turno ciclico es primero inicializar todas las variables que seran utilizadas en los procesos
de hilos por ejemplo: estomagos, eat, numero de filosofos
Luego realizaremos o ejecutaremos los hilos,el hilo llevara siempre un dato que especificara a aun filosofo en particular tambien 
veremos la creacion de elementos de forma random y tendremos un sleep para hacer que los numeros random sea diferentes en cada hilo 
luego en el proceso de comer o pensar que realiza un filosofo para solucionar este proceso nos enfocaremos el que comera ya que el 
llevara el tiempo que demora en comer pero este tiempo a la par tambien es el tiempo que los demas filosofos estan pensando(filosofos 
que no es su turno) de esta forma podemos manejar estos procesos tranquilamente cabe resaltar que utilizare un mutex para lograr que los 
hilos se ejecuten uno a la vez realizo este procedimiento para poder presentarles en consola los procesos o acciones que se realizan en 
mi programa de forma entendible y no exista complicaciones con otros hilos que intentan ocupar la consola al mismo tiempo, luego en mi 
programa en la parte que el filosofo esta comiendo habra un if que controlara si el filosofo se encuentra lleno o no, si lo esta 
realizara un break para no seguir ya que hemos mencionado cuando un filosofo come ahora hablaremos cuando este piensa tendremos aqui un 
if que nos ayudara a llegar al proceso de que un filosofo pueda morir y realizaremos un usleep (sirve para que el proceso siguiente se 
realize despues de un cierto tiempo) para el nuevo hilo que ejecutaremos este se encargara de verificar si despues de un tiempo si el 
filosofo que se encuentra en riesgo de morir no pudo comer algo morira luego otra funcion que podemos mencionar es la de estado esta 
proporciona informacion sobre los filosofos que murieron mi programa puede seguir ejecutandose sin problemas a pesar de este suceso ya 
que por lo que vimos el turno ciclico se realiza de forma lineal y un unico filosofo tiene turno asi que es facil poner restricciones 
que logren reacomodar al sistema y el programa pueda seguir ejecutandose.

Por varios turnos:
El funcionamiento de mi programa de varios turnos empieza inicializando con todos los elementos que se utilizara como por ejemplo: 
cantidad, los estomagos, eat(que ahora son varios platos)
Y ahora comenzaremos a repartir las tres fichas que nos ayudaran a repartir de forma mas rapida los turnos que tendran los filosofos, 
estas fichas se reparten y luego procederemos a inicializar nuestros hilos pero ahora el hilo llevara la informacion de tres datos de 
los cuales especificaran a tres filosofos que tienen una ficha(turno) este proceso tendra un mutex que nos ayudara a presentar todas las 
acciones o procedimientos que realiza nuestro programa de varios turnos para no tener ningun inconveniente en nuestra consola, para que 
no exista el problema de que varios hilos muestren su informacion al mismo tiempo, despues de aclarar el uso de nuestro mutex veremos la 
creacion de datos random pero ahora contamos con tres filosofos que se encuentran comiendo la solucion sera enfocarnos en el tiempo del 
filosofo que se demora mas en comer este tiempo sera igual al de los que no tienen ficha(los que estan pensando) pero aqui tenemos un 
detalle de que tendremos a filosofos que tienen ficha y estan pensando porque sucede eso es porque no todos los filosofos que tienen 
ficha demoran lo mismo por entonces habra filosofos que terminen antes y posteriormente se pondran a pensar, la solucion a este problema 
era que tenga su propio proceso de pensar muy aparte al de los que no tienen ficha y un detalle a agregar esque el tiempo que emplea no 
es igual al tiempo que emplearon a los que no tienen ficha.
Tambien tendremos un if que nos ayudara a saber cuando un filosofo esta lleno siempre cuando este se encuentre comiendo y halla llegado 
a su limite, tambien tendremos otro if que ayudara a saber cuando un filosofo esta a punto de morir siempre cuando el filosofo halla 
estado gastando energia en este proceso al haber una muerte de un filosofo procederemos a terminar la ejecucion de programa ya que el 
proceso a sido interrumpido por una muerte de un filosofo tomamos esta decision porque es mas complicado intentar que el programa siga 
ejecutandose ya que contamos con varios filosofos actuando a la vez y se pueda presentar varios turnos repetitivos por parte de un 
filosofo. 


Video:
https://drive.google.com/file/d/1LGdMrciz5rQkWvmuau7CxOg1IqNDdQyo/view?usp=sharing


