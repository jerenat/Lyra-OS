int atoi(char *palabra)
{
	int numero = 0;
	int i;
	int longitud = strlen(palabra);

	// Determinar la longitud de la secuencia de dígitos válidos
	for (i = 0; i < longitud; i++)
	{
		if (palabra[i] >= '0' && palabra[i] <= '9')
		{
			numero++;
		}
		else
		{
			break;
		}
	}

	int y = 0;
	// Convertir la secuencia de dígitos en un número entero
	for (i = 0; i < numero; i++)
	{
		y *= 10;
		y += palabra[i] - '0';
	}

	return y;
}