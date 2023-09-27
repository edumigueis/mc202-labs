#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "dequef.h"


int main(void) {

  char cmd[13];
  float f;
  int i, st = 1;
  dequef* D = NULL;

  while (1) {
    scanf("%s",cmd);

    if (strcmp(cmd,"create") == 0) {
      scanf("%i %f",&i,&f);

      if (D != NULL)
        df_free(D);

      D = df_alloc(i,f);
      if (!D) {
        printf("Unable to create a dequef.\n");
        return errno ? errno : 1;
      }
    }

    else if (strcmp(cmd,"push") == 0) {
      scanf("%f",&f);
      st = df_push(D,f);
    }

    else if (strcmp(cmd,"pop") == 0) {
      if (df_size(D) > 0)
        f = df_pop(D);
    }

    else if (strcmp(cmd,"inject") == 0) {
      scanf("%f",&f);
      st = df_inject(D,f);
    }

    else if (strcmp(cmd,"eject") == 0) {
      if (df_size(D) > 0)
        f = df_eject(D);
    }

    else if (strcmp(cmd,"set") == 0) {
      scanf("%i %f",&i,&f);
      if (i >= 0 && i < df_size(D))
        df_set(D,i,f);
    }

    else if (strcmp(cmd,"get") == 0) {
      scanf("%i",&i);
      if (i >= 0 && i < df_size(D))
        printf("D[%d] == %.1f\n",i,df_get(D,i));
    }

    else if (strcmp(cmd,"is-empty?") == 0) {
      if (df_size(D) == 0)
        printf("empty\n");
      else
        printf("not empty\n");
    }

    else if (strcmp(cmd,"print") == 0) {
      df_print(D);
    }

    else if (strcmp(cmd,"exit") == 0) {
      df_free(D);
      return 0;
    }

    else {
      printf("Ups! invalid command: %s.\n",cmd);
      df_free(D);
      return 1;
    }

    if (st == 0) {
      printf("Unable to resize.");
      df_free(D);
      return errno ? errno : 1;
    }
  }
}
