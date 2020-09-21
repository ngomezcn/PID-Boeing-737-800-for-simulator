# Vuelo autónomo para la aeronave    F-4 Phantom II

# Ejes de control

---

Input de entrada: 

Roll

Yaw

Pitch

![Vuelo%20auto%CC%81nomo%20para%20la%20aeronave%20F-4%20Phantom%20II%208a9becd143eb497295e3a338c7121ccd/1200px-Flight_dynamics_with_text_ortho.svg.png](Vuelo%20auto%CC%81nomo%20para%20la%20aeronave%20F-4%20Phantom%20II%208a9becd143eb497295e3a338c7121ccd/1200px-Flight_dynamics_with_text_ortho.svg.png)

# Busqueda de las direcciónes con Cheat Engine

---

Para que el controlador de vuelo pueda interactuar con X-Plane es necesario poder acceder a la memoria del juego para modificar y leer ciertas variables, he utilizado CE para encontrar la ubicación de las variables en memoria.

X-Plane es un juego bastante complejo lo que hace que exista una cantidad considerable de punteros multinivel desde la direccion dinamica hasta la estatica. 

### Busqueda de la dirección dinamica

Para que sea mas comodo buscar el valor exacto de las variables he utilizado el plugin **Data Ref Editor**, este plugin despliega una ventana donde se puede buscar y visualizar todos los data ref en tiempo real y tambien permite modificarlos.

[DataRefEditor](http://www.xsquawkbox.net/xpsdk/mediawiki/DataRefEditor)

### Busqueda de la dirección estatica

Para encontrar la dirección estatica he utilizado el Pointer Scan de Cheat Engine, he escogido las direcciónes estaticas con menos punteros multinivel para que sea mas facil escribirlo en C++

# DataRefs incluidos en el codigo

---

En la siguiente tabla estan los datarefs junto con su dirección estatica, practicamente todos los punteros son multinivel. Algunos dataref solo permiten lectura y al editarlo se volvera a rescribir por una subrutina del juego.

En la captura de pantalla como ejemplo se muestara como se deberia interpretar la columna **Dirección estatica y Offsets** del primera linea de la tabla, de esta manera es como se debe introducir en Cheat Engine.

![Vuelo%20auto%CC%81nomo%20para%20la%20aeronave%20F-4%20Phantom%20II%208a9becd143eb497295e3a338c7121ccd/CheatEngineAddAddres.bmp](Vuelo%20auto%CC%81nomo%20para%20la%20aeronave%20F-4%20Phantom%20II%208a9becd143eb497295e3a338c7121ccd/CheatEngineAddAddres.bmp)

---

[Tabla de DataRefs](https://www.notion.so/b20c74b863024c1f8db76446eaa110f9)

# Leer los valores de las direcciónes finales mediante punteros multinivel en C++

---

### Configuración del e**ntorno para Visual Studio 2019.**

- Utilizar Solution Configuration en modo **Release**
- Utilizar Solution Plataform en **x64 bits**
- Character Set debe utilizar **Multi-Byte**

### Codigo de ejemplo, Como leer valor a traver de 7 punteros multinivel.

Codigo de ejemplo para poder leer la dirección estatica del dataref *flap_request* a la dirección se accede atraves de 7 punteros multinivel. 

El primer paso 

```cpp
DWORD_PTR  dwGetModuleBaseAddress(TCHAR *lpszModuleName, DWORD pID) {
	DWORD_PTR  dwModuleBaseAddress = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);
	MODULEENTRY32 ModuleEntry32 = { 0 };
	ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnapshot, &ModuleEntry32)){
		do {
			if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0){
				dwModuleBaseAddress = (DWORD_PTR)ModuleEntry32.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnapshot, &ModuleEntry32));
	}
	CloseHandle(hSnapshot);
	return dwModuleBaseAddress;
}

int main() {
	DWORD pID;
	DWORD_PTR  off1, off2, off3, off4, off5, off6;
	DWORD_PTR baseAddress;
	DWORD_PTR  flapAddres;
	float currentFlap;
	char moduleName[] = "X-Plane.exe";
	HWND hGameWindow;
	HANDLE pHandle;

	//Obtener identificador.
	hGameWindow = FindWindow(NULL, "X-System");
	GetWindowThreadProcessId(hGameWindow, &pID);
	pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);

	//Obtener la dirección base del cliente.
	DWORD_PTR  clientBase = dwGetModuleBaseAddress(_T(moduleName), pID);

	//Leer el valor de las direcciónes.
	ReadProcessMemory(pHandle, (LPCVOID)(clientBase + 0x02662358), &baseAddress, sizeof(baseAddress), NULL);
	std::cout << "Dirección base: " << std::hex << baseAddress << std::endl;
	ReadProcessMemory(pHandle, (LPCVOID)(baseAddress + 0x10), &off1, sizeof(off1), NULL);
	std::cout << "Offset 1: " << std::hex << off1 << std::endl;
	ReadProcessMemory(pHandle, (LPCVOID)(off1 + 0x10), &off2, sizeof(off2), NULL);
	std::cout << "Offset 2: " << std::hex << off2 << std::endl;
	ReadProcessMemory(pHandle, (LPCVOID)(off2 + 0x0), &off3, sizeof(off3), NULL);
	std::cout << "Offset 3: " << std::hex << off3 << std::endl;
	ReadProcessMemory(pHandle, (LPCVOID)(off3 + 0x8), &off4, sizeof(off4), NULL);
	std::cout << "Offset 4: " << std::hex << off4 << std::endl;
	ReadProcessMemory(pHandle, (LPCVOID)(off4 + 0x20), &off5, sizeof(off5), NULL);
	std::cout << "Offset 5: " << std::hex << off5 << std::endl;
	ReadProcessMemory(pHandle, (LPCVOID)(off5 + 0x18), &off6, sizeof(off6), NULL);
	std::cout << "Offset 6: " << std::hex << off6 << std::endl;
		
	flapAddres = off6 + 0xDC;
	std::cout << "Dirección: " << std::hex << flapAddres << std::endl;
	ReadProcessMemory(pHandle, (LPCVOID)(flapAddres), &currentFlap, 4, NULL);
	std::cout << "Valor: " << currentFlap << std::endl;
}
```

# Explicación de las funciónes del codigo.

---

### **Entorno para Visual Studio 2017.**

- Utilizar Solution Configuration en modo **Release**
- Utilizar Solution Plataform en **x64 bits**
- Character Set debe utilizar **Multi-Byte**

// Falta incluir el codigo y explicar como funciona

# Control PID

---

El controlador PID se resume a estas tres constantes que deben ser calibradas dependiendo de la situación.

- **Kp -** Presente.
- **Kd -** Futuro.
- **Ki  -** Pasado.

El orden a seguir para calibrar las tres constantes es primero **Kp**, segundo **Kd** y finalmente **Ki**.

![Vuelo%20auto%CC%81nomo%20para%20la%20aeronave%20F-4%20Phantom%20II%208a9becd143eb497295e3a338c7121ccd/maxresdefault.jpg](Vuelo%20auto%CC%81nomo%20para%20la%20aeronave%20F-4%20Phantom%20II%208a9becd143eb497295e3a338c7121ccd/maxresdefault.jpg)

- Utilizar Solution Configuration en modo **Release**
- Utilizar Solution Plataform en **x64 bits**
- Character Set debe utilizar **Multi-Byte**

# GUI con Qt

---

Para crear la GUI voy a utilizar Chromium Embedded Framework

asdasdasdasd