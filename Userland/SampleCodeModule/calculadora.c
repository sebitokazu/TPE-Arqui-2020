#include "include/calculadora.h"
#include "include/stdio.h"
#include "include/strings.h";
#include "include/graphicslib.h"

void imprimirResultado(char *resultado);
int charToInt(char c);
int calcularExpresion(char *input);
int addNum(char *input, int pos, int *enteros, int *decimales, int posNum);
int potDiez(int num);
int getInversePrefija(char *input, int cant);
int emptyTillParenthesis(char *buffer, int posBuffer, char *pila, int posPila);
void inverseString(char *input, int cant);
int bufferOrPila(char c, char *pila, int posPila, char *buffer, int posBuffer);
int getPrecedencia(char c);
int scanfIO(char *buff);
int isValid(char c);
int isNumber(char c);
int isOperation(char c);
int addNumToString(int n, int i, char *numFinal);
int getDecena(int n);
char intToChar(int n);
int addDecimalesToString(int n, int i, char *numFinal);
int makeOperation(int *enteros, int *decimales, int pos, char c);
static void newEntry();
static void newLine();
static void clear();

static char input[64];
static int buffer_pos = 0;

static int currentX = 0;
static int currentY = 0;

static int width;
static int height;
static int is_running = 1;

const char msg[205] = "Bienvenido a la calculadora\nPresione = para evaluar una expresion\n\
Presione 'd' para borrar la linea actual\nPresione 'c' para limpiar la pantalla";

int runCalculadora(int _width, int _height)
{
    width = _width;
    height = _height;
    if (is_running)
    {
        currentX = 0;
        currentY = 0;
        puts(msg, currentX, currentY);
        currentY += 4;
    }
    else
    {
        is_running = 1;
    }
    if (currentX == 0)
    {
        newEntry();
    }

    int cant = scanfIO(input), seguir = 1;
    while (cant >= 0)
    {
        if (cant > 0)
        {
            seguir = getInversePrefija(input, cant);
            if(seguir){
                seguir = calcularExpresion(input);
                if (seguir)
                    imprimirResultado(input);
            }
        }
        if(currentX!=1)
            newEntry();
        cant = scanfIO(input);
    }
    return 0;
}

void imprimirResultado(char *resultado)
{
    if(currentX + 3 >= width)
        newLine();
    puts(" = ", currentX, currentY);
    currentX += 3;
    currentX+=puts(resultado,currentX,currentY);
    if(currentX>=width){
        currentY++;
    }
    newLine();
}

//Convirte un char en un int
int charToInt(char c)
{
    return c - '0';
}

//Devuelve el resultado final de toda la expresion
int calcularExpresion(char *input)
{
    int enteros[40];
    int decimales[40];
    int posNum = 0;
    
    for (int i = 0; i < strlen(input); i++)
    {
        if (isNumber(input[i]))
        {
            i = addNum(input, i, enteros, decimales, posNum++);
            if (i == 0)//Solamente si se ejecuta terminar
            {
                return -1;
            }
            
        }
        if (input[i] != '&')
        {
            int finish = makeOperation(enteros, decimales, --posNum, input[i]);
            if(finish ==0)
                return -1;
        }
    }
    
    if(enteros[0]<0){
        char auxiliar[11];
        posNum=uintToBase(enteros[0]*(-1), auxiliar, 10);
        auxiliar[posNum++] = '.';
        input[0]='-';
        for(int i=1; i<=posNum;i++)
            input[i]=auxiliar[i-1];
        posNum++;
    }else{
        posNum=uintToBase(enteros[0], input, 10);
        input[posNum++] = '.';
    }
    char auxi[5];
    int j=0,cant=uintToBase(decimales[0], auxi, 10);
    while((cant+j)<4){
        input[posNum++]='0';
        j++;
    }
    while(j<4){
        input[posNum++]=auxi[j++];
    }
    input[posNum] = '\0';
    return 1;
}

//Agrega los decimales a numFInal
int addDecimalesToString(int n, int i, char *numFinal)
{
    int mult = 1000;
    while (mult != 0)
    {
        numFinal[i++] = intToChar(n / mult);
        n - ((n / mult) * mult);
        mult = mult / 10;
    }
    return i;
}

//Agrega a numFinal el numero entero
int addNumToString(int n, int i, char *numFinal)
{
    while (n > 0)
    {
        int decena = getDecena(n);
        numFinal[i++] = intToChar(n / potDiez(decena));
        decena = decena / 10;
    }
    return i;
}

//devuelve la longitud de n-1
int getDecena(int n)
{
    if (n >= 0 || n < 10)
        return 0;
    return 1 + getDecena(n / 10);
}

//Devuelve el valor de un int de 1 digito como char.
char intToChar(int n)
{
    return '0' + n;
}

//Hace la operacion correspondiente
int makeOperation(int *enteros, int *decimales, int pos, char c)
{  
    double n1 = (enteros[pos - 1] + ((double)decimales[pos - 1] / 10000.0)), n2 = (enteros[pos] + ((double)decimales[pos] / 10000.0));
    switch (c)
    {
    case '+':
        n2 += n1;
        break;
    case '-':
        n2 -= n1;
        break;
    case 'x':
        n2 *= n1;
        break;
    case '%':
        if (n1 == 0.0){
            puts("NO SE PUEDE DIVIDIR POR CERO", currentX, currentY++);
            return terminarExpresion();
        }
        n2 /= n1;
        break;
    }
    int entero = (int)n2;
    enteros[pos - 1] = entero;
    n2 -= (entero * 1.0);
    n2 *= 10000;
    entero = (int)n2;
    decimales[pos - 1] = entero;
    return 1;
}

//Agrega el numero a la pila. Devuelve la pos + la longitud del numero. Si devuelve 0, entonces hay que terminar.
int addNum(char *input, int pos, int *enteros, int *decimales, int posNum)
{
    int aux = pos + 1, entero = charToInt(input[pos]), decimal = 0, potencia = 1;
    while (isNumber(input[aux]))
    {
        entero += (charToInt(input[aux]) * potDiez(potencia++));
        aux++;
    }
    if (input[aux] == '.')
    {
        if(entero>=10000)
            return terminarExpresion();
        decimal = entero * potDiez(4 - (aux - pos));
        aux++;
        potencia = 1;
        entero = charToInt(input[aux++]);
        while (isNumber(input[aux]))
            entero += (charToInt(input[aux++]) * potDiez(potencia++));
        if (input[aux] == '.')
        {
            return terminarExpresion();
        }
    }
    enteros[posNum] = entero;
    decimales[posNum] = decimal;
    return aux;
}

//Devuelve 10 ^ num
int potDiez(int num)
{
    if (num == 0)
        return 1;
    if (num == 1)
        return 10;
    return 10 * potDiez(num - 1);
}

//Devuelve un char* con la expresion pasada a prefija pero invertida. Chequea que no hayan errores de sintaxis.
int getInversePrefija(char *input, int cant)
{
    char ultimo;
    if (cant == 0)
    {
        return terminarExpresion();
    }
    else if (cant == 1)
    {
        if(!isNumber(input[0]))
            return terminarExpresion();
        ultimo = '\0';
    }
    else
    {
        inverseString(input, cant);
        ultimo = input[cant - 1];
    }

    char pila[32];
    char buffer[64];
    int cantParentesis = 0, posBuffer = 0, posPila = 0, printDot = 0;

    if (ultimo == '.' || ultimo == ')' || isOperation(ultimo))
        return terminarExpresion();
    if (cant > 1)
        if (input[0] == '.' || input[0] == '(' || isOperation(input[0]))
            return terminarExpresion();
    if (input[0] == ')')
    {
        pila[posPila++] = ')';
        cantParentesis++;
    }
    else
    {
        buffer[posBuffer++] = input[0];
    }

    for (int i = 1; i < cant - 1; i++)
    {
        char aux = input[i];
        switch (aux)
        {
        case ')':
            if (!isNumber(input[i + 1]) && input[i + 1] != ')')
                return terminarExpresion();
            cantParentesis++;
            pila[posPila++] = aux;
            break;
        case '(':
            if (cantParentesis==0 || (!isOperation(input[i + 1]) && input[i+1]!='('))
                return terminarExpresion();
            cantParentesis--;
            int diferencia = emptyTillParenthesis(buffer, posBuffer, pila, posPila);
            posBuffer += diferencia;
            posPila -= diferencia;
            if (diferencia > 0)
                pila[--posPila] = '\0';
            break;
        case '+':
        case '-':
        case '%':
        case 'x':
            if (!isNumber(input[i + 1]) && input[i+1]!=')'){
                return terminarExpresion();
            }
            int cambio = 0;
            cambio = bufferOrPila(aux, pila, posPila, buffer, posBuffer);
            if (cambio > 0)
            {
                posBuffer += cambio;
                posPila -= cambio;
                pila[posPila] = '\0';
            }
            else
            {
                posPila++;
                printDot = 1;
            }
            break;
        case '.':
            if (!isNumber(input[i + 1]))
            {
                return terminarExpresion();
            }
            buffer[posBuffer++] = aux;
            break;
        default:
            if (printDot)
                buffer[posBuffer++] = '&';
            printDot = 0;
            buffer[posBuffer++] = aux;
        }
    }
    if (printDot)
        buffer[posBuffer++] = '&';
    printDot = 0;
    if (ultimo == '(')
    {
        if (cantParentesis!=1)
            return terminarExpresion();
        cantParentesis--;
        int diferencia = emptyTillParenthesis(buffer, posBuffer, pila, posPila);
        posBuffer += diferencia;
        posPila -= diferencia;
        if (diferencia > 0)
            pila[--posPila] = '\0';
    }
    else
    {
        buffer[posBuffer++] = ultimo;
    }

    if(cantParentesis!=0)
        return terminarExpresion();

    if (pila[0] != '\0')
    {
        int cambio = emptyTillParenthesis(buffer, posBuffer, pila, posPila);
        posBuffer += cambio;
        if ((posPila - cambio) > 0)
            return 0;
    }

    buffer[posBuffer++] = '\0';
    for (int i = 0; i < posBuffer; i++)
    {
        input[i] = buffer[i];
    }
    //input[posBuffer]='\0';  
    return 1;
}

//Devuelve 0
int terminarExpresion()
{
    newLine();
    puts("La expresion algebraica tiene un error", currentX, currentY);
    newLine();
    return 0;
}

//devuelve la cantidad de operaciones que saca de la pila y pone en el buffer
int emptyTillParenthesis(char *buffer, int posBuffer, char *pila, int posPila)
{
    int diferencia = 0;
    posPila--;
    while (posPila >= 0 && pila[posPila] != ')')
    {
        buffer[posBuffer++] = pila[posPila];
        pila[posPila--] = '\0';
        diferencia++;
    }
    buffer[posBuffer] = '\0';
    pila[posPila]='\0';
    return diferencia;
}

//Da vuelta input. Es decir el ultimo char, en la posicion del primero, etc.
void inverseString(char *input, int cant)
{
    char *resp = "";
    int i = 0;
    cant--;
    char aux;
    while (i < cant)
    {
        aux = input[cant];
        input[cant--] = input[i];
        input[i++] = aux;
    }
}

//Devuelve un numero mayor a 0 si agrego el caracter al buffer. Devuelve 0 si lo agrega a la pila.
int bufferOrPila(char c, char *pila, int posPila, char *buffer, int posBuffer)
{
    if (posPila == 0)
    {
        pila[posPila++] = c;                         
        return 0;
    }
    if (getPrecedencia(pila[posPila - 1]) > getPrecedencia(c))
    {
        buffer[posBuffer++] = c;
        posPila--;
        return 1 + bufferOrPila(c, pila, posPila, buffer, posBuffer);
    }
    pila[posPila++] = c;
    pila[posPila]='\0';
    
    return 0;
}

//Devuelve el valor de precedencia(0,1,2)
int getPrecedencia(char c)
{
    switch (c)
    {
    case '+':
        return 1;
        break;
    case '-':
        return 1;
        break;
    case 'x':
        return 2;
        break;
    case '%':
        return 2;
        break;
    case ')':
        return 0;
        break;
    default:
        return 0;
    }
}

//Escanea unicamente caracteres validos, hasta que ingresen un '='
int scanfIO(char *buff)
{
    char c = 0;
    c = getchar();
    while (c != '=')
    {
        int aux = isValid(c);
        switch (aux)
        {
        case 0: // backspace
            if (buffer_pos > 0){
                buff[buffer_pos] = '\0';
                putchar('\b',currentX--, currentY);
                buffer_pos--;
            }
            break;
        case 1: // borrar linea
            for (buffer_pos; buffer_pos > 0;buffer_pos--){
                buff[buffer_pos] = '\0';
                putchar('\b', currentX--, currentY);
            }
                break;
        case 2:
            if (getCtrlState() == 1){
                is_running = 0;
                return CHANGEWINDOW;
            }
            break;
        case 3:
            if (currentX <width){
                buff[buffer_pos++] = c;
                putchar(c,currentX++,currentY);
            }
            break;
        case 4: //borrar todo
            clear();
            buffer_pos = 0;
            return 0;
        default:
            break;
        }
        c = getchar();
    }
    buff[buffer_pos] = '\0';
    int copy_cant = buffer_pos;
    buffer_pos = 0;
    return copy_cant;
}

//Devuelve el numero correspondiente al dato ingresado
int isValid(char c)
{
    if (isNumber(c) || isOperation(c) || c == '(' || c == ')' || c == '.')
    {
        return 3;
    }
    switch (c)
    {
    case '\b': //backspace
        return 0;
    case 'd': //borrar todo
        return 1;
    case 'q':
        return 2;
    case 'c':
        return 4;
    default:
        return 5;
    }
}

//Devuelve 1 si es un numero. De lo contrario devuelve 0;
int isNumber(char c)
{
    return (c >= '0' && c <= '9');
}

//Devuelve 1 si es una operacion. De lo contrario devuelve 0;
int isOperation(char c)
{
    if (c == '+' || c == '-' || c == 'x' || c == '%')
        return 1;
    return 0;
}

static void newEntry()
{
    putchar('#', currentX, currentY);
    currentX++;
}
static void newLine()
{
    currentX = 0;
    currentY++;
    if (currentY >= height)
    {
        scroll();
        currentY = height - 1;
    }
}

static void clear()
{
    clear_screen();
    currentX = 0;
    currentY = 0;
}