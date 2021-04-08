/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdltools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenani <abenani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:13:01 by abenani           #+#    #+#             */
/*   Updated: 2021/02/22 10:54:01 by abenani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

int		startsdl(t_sdl *sdl)
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		if ((sdl->win = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_UNDEFINED,
						SDL_WINDOWPOS_UNDEFINED, W_WIDTH,
						W_HEIGHT, SDL_WINDOW_SHOWN)))
		{
			if ((sdl->rend = SDL_CreateRenderer(sdl->win, -1,
							SDL_RENDERER_SOFTWARE)))
				return (1);
			else
				SDL_DestroyWindow(sdl->win);
		}
		else
			SDL_Quit();
	}
	ft_putendl(SDL_GetError());
	return (0);
}

int		exitsdl(t_sdl sdl)
{
	SDL_Event e;

	if (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN &&
					e.key.keysym.sym == SDLK_ESCAPE))
		{
			SDL_DestroyRenderer(sdl.rend);
			SDL_DestroyWindow(sdl.win);
			SDL_Quit();
			return (1);
		}
	}
	return (0);
}

void	draw(SDL_Renderer *rend, t_color *colors)
{
	int		i;
	int		j;
	t_color color;

	SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
	j = 0;
	while (j < W_HEIGHT)
	{
		i = 0;
		while (i < W_WIDTH)
		{
			color = colors[W_WIDTH * j + i];
			SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
			SDL_RenderDrawPoint(rend, i, j);
			i++;
		}
		j++;
	}
	SDL_RenderPresent(rend);
	free(colors);
}
