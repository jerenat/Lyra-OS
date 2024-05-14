void cls()
{
	char *text_video = (char *)0xB8000; // direccion de la video
	int i;

	for (i = 0; i < 4000; i++)
	{						  // toda la pantalla
		*text_video++ = 0x00; // en color negro
	}
}