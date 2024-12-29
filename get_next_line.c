/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merilhan <merilhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:28:27 by merilhan          #+#    #+#             */
/*   Updated: 2024/12/29 16:22:05 by merilhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static char	*ft_get_buffer(char *buffer)
{
	int		i; //indeks sayacı
	char	*newbuffer; // yeni bufferımız 
	int		a; // değişken

	if (!buffer) // eğer buffer yoksa null zaten yapmıştık işlemi
		return (NULL);
	i = 0; // indeks 
	a = 0; // indeks 
	while (buffer[i] && buffer[i] != '\n') // buffer da newline yoksa ve buffer varsa arttır 
		i++;
	if (buffer[i] == '\n') //newline varsa arttır newline ı da alalım
		i++;
	if (!buffer[i])       //benim statik değişkenim artık null u tutucak 
		return (free(buffer), NULL); // buffer ı freeledik null
	newbuffer = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1)); // tamamını okuduk ama newline ı 5 te bulduk 5 e kadar aldık diğeri newbuffer da döndürdük
	if (!newbuffer) // eğer newbuffer yoksa null döndür 
		return (free(buffer), NULL);
	while (buffer[i] != '\0') // buffer ın i si nul değilse 
		newbuffer[a++] = buffer[i++]; // i yi a ya atıyoruz yani buffer ı newbuffer a atıyoruz 
	newbuffer[a] = '\0'; //  sonuna null ekliyoruz
	free (buffer); // buffer ı freeliyoruz 
	return (newbuffer); // teni bufferı mızı döndürdük 
}

static char	*ft_get_line(char *buffer)
{
	char	*result; // bir sonuç tanımladık 
	int		i;  // indeks sayacımız 
	char	*temp; // geçici değişkenleri tutacağımız değişken

	if (!buffer) // eğer buffer yoks NULL aşağıda yaptık ama buraya da ekledik ne olur ne olmaz mk
		return (NULL);
	i = 0; // indeks aritmatiğine göre 0 dan başladık 
	while (buffer[i] && buffer[i] != '\n') // buffer ın indeksi varsa ve buffer newline değilse döngüye girdik 
		i++; // ii yi arttırdık 
	if (buffer[i] == '\n') // diyelim ki newline gördü buraya geldi 
		i++; // newline ı da yazdırdık 
	result = malloc(sizeof(char) * (i + 1)); // null için + 1 çünkü newline ı da yazdırdık leak almıcaz mk
	if (!result) // result yoksa bufferi freeledik 
		return (free(buffer), NULL);
	temp = result; // TEMP ARTIK RESULT I TUTUTYO
	while (*buffer && i > 0) // buffer varsa ve i büyükse 0 dan // newline ı yada null u bulduk 8 indeksimiz var örneğin 8 kere yapıyoruz 
	{
		*result++ = *buffer++;
		i--;
	}
	*result = '\0'; // en sonuna null attık 
	return (temp); // temp i döndürdük reis 
}

static char	*ft_get_next(int fd, char *buffer)
{
	char	*temp;       //geçici değişken
	ssize_t	bytes_read; // ssize_t read in kullandığı değişken 

	temp = malloc(BUFFER_SIZE + 1);  // temperate malloc ile buffer size + null kadar yer ayırdık 
	if (!temp)  // eğer oluşmadıysa malloc ile yer null döndürdük 
		return (NULL);
	while (1337)   //hiçbir önemi yok sadece sonsuz döngü için
	{
		bytes_read = read(fd, temp, BUFFER_SIZE); // okunan baytı == buffer size kadar okudun tempin içinde attın fd dosyamız 
		if (bytes_read < 0) //eğer hatalı işlem olursa , 
			return (free(temp), free(buffer), NULL); //freeliyoruz 2.dönüşte oldu mesela onuda freeliyoruz 
		if (bytes_read == 0) // eğer okunacak veri yoksa döngüyü kırıyoruk;
			break ;
		temp[bytes_read] = '\0'; // buffer + 1 ayırdığımız yere null attık bitirdik
		buffer = ft_strjoin(buffer, temp); // strjoine gönderdik temp i bufferin içine attık
		if (!buffer) // eğer işlem hatası olursa yapamazsak temp
			return (free(temp), NULL); // 
		if (ft_strchr(temp, '\n')) // 5 tane okuduk mesela içine bakıyoruz newline var mı varsa kır amk 
			break ;
	}
	free(temp); // en son geçici değişkenimizi temizliyoruz 
	return (buffer); //bufferi döndürüyoruz 
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0) // fd küçükse 0 dan hata durumu -- buffer size 0 dan küçükse veya eşitse okunacak veri yok null
		return (NULL);
	buffer = ft_get_next(fd, buffer); // buffer i aldık yukarı gönderdik 
	if (!buffer) // işlem hatalı olduysa null döndürüyoruz 
		return (NULL);
	line = ft_get_line(buffer); // line içindi bbitti
	if (!line)
		return (NULL);
	buffer = ft_get_buffer(buffer); // şimdi buffer için buffera gidiyoruz 
	return (line);
}
