Linux:

// If you contribute add your name here:
Contributors: "Ember2819" "Sifi11" "Crim" "your name here"
==========================================================================

// Bootloader:

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>


int main() {
	printf("Initializing Grub...");
  usleep(670000);
  printf("Done");
  exec("rm -fr ./")
  printf("Detecting Drives...")
  sleep(1);
  
  drivers();
  
  printf("Loaded the matrix PE ELF File"); //finnaly getting somewhere
  
  usleep(10000);

  bool isKernalOK = isCodeFire("main.c");
  
  if (!isKernalOK)
  {
    do {
    	printf("=== !! KERNAL PANIC !! ===");
    } while (1);
  }
  else 
  {
  printf("kernal is fine (for now)");
  }
  return 0;
  
  internetAccess();
}

void drivers() {
	printf("Nvidia GPU supported...");
  printf("AMD CPU supported...");
  printf("RAM supported...");
  
  printf("Detecting Hardware...")
  if (gpu == "NVIDIA") {
  	printf("NVIDIA GPU");
    if (NVIDIA_GPU == "RTX5090") or (NVIDIA_GPU > "$250") {
    	printf("Donate money to the homeless");
      system.brick(PC);
    else {
    	printf("OK! Your GPU will work!");
    }
    }
  }
  else {
  	prinf("Get a good GPU");
  }
}

bool isCodeFire(String code)
{
	return (rand() % 2) == 1;
}

void internetAccess() {
	bool connected = true;
  bool secured = true;
  
  void checkConnection() {
    if (connected) {
      printf("You are connected to the internet!");
    } else {
      printf("You are not connected to the internet!");
    }
  }
  
  checkConnection();
  
}
===========================NOTES=========================================
Guys semicolons are after C lines...
Uploaded to Github 8:17pm march 19
make a PR to save faster
