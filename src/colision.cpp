#include "map.hpp"
#include "player.hpp"

void	jump(float r, map &map, player &pl)
{

}

int	colision(int dx, int dy, int lx, int ly, map &map, player &pl)
{
  int	x = 0, y = 0;
  int	cx, cy;

  while (x < lx)
    {
      cx = (pl._pos.x + dx + x) / 32;
      cy = (pl._pos.y + dy) / 32;
      if (map._case[cy][cx].n != VIDE && map._case[cy][cx].n > 0)
	return (1);
      x++;
    }
  while (y < ly)
    {
      cx = (pl._pos.x + dx) / 32;
      cy = (pl._pos.y + dy + y) / 32;
      if (map._case[cy][cx].n != VIDE && map._case[cy][cx].n > 0)
	return (1);
      y++;
    }
  return (0);
}

int	ok(map &map, player &pl)
{
  if (pl._v.x < 0)
    {
      if (!colision(0, 0, 0, 32, map, pl))
	return (1);
    }
  else if (pl._v.x > 0)
    {
      if (!colision(32, 0, 0, 32, map, pl))
        return (1);
    }
  else
    return (1);
  return (0);
}

void	deplacement(map &map, player &pl)
{
  int	friction;
  int cx, cy;

  cx = pl._pos.x / 32;
  cy = (pl._pos.y + 32) / 32;
  friction = map._case[cy][cx].f;
  if (pl._dpl[0])
    {
      if (ok(map, pl))
	{
	  if (pl._v.x < 1)
	    pl._v.x += 0.004;
	}
      else
	{
	  pl._v.x = 0;
	}
    }
  else
    {
      if (ok(map, pl))
	{
	  if (pl._v.x > 0)
	    pl._v.x -= 0.001 * friction;
	}
      else
	{
	  pl._v.x = 0;
	}
    }


  if (pl._dpl[1])
    {
      if (ok(map, pl))
	{
	  if (pl._v.x > -1)
	    pl._v.x -= 0.004;
	}
      else
	{
          pl._v.x = 0;
	}
    }
  else
    {
      if (ok(map, pl))
	{
	  if (pl._v.x < 0)
	    pl._v.x += 0.001 * friction;
	}
      else
	{
          pl._v.x = 0;
	}
    }
}

void	gravity(map &map, player &pl)
{
  int	cx, cy;

  if (!colision(1,32,31,0, map, pl))
    {
      if (pl._v.y < 1)
        pl._v.y += 1;
    }
  else
    {
      pl._v.y = 0;
      cx = pl._pos.x / 32;
      cy = (pl._pos.y + 33) / 32;
      jump(map._case[cy][cx].r, map, pl);
    }
}
