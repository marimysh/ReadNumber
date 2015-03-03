/*class FindSymbol
{
public:
  {
    //Характеристические функции
    bool LineOne();
    bool LineTwo();
    bool LineThree();
    
    bool RoundOne();
    bool RoundTwo();
    bool RoundThree();
    
    bool GravityCenterCenter();
    bool GravityCenterLow();
    bool GravityCenterHi();
    bool GravityCenterLeft();
    bool GravityCenterRight();
    
    //TODO: возможность выбирать карту для каждого символа
    bool EqualMapSymbol();
    
    bool IslandOne();
    bool IslandTwo();
    bool IslandThree();
    
    //дозакончить фигуру и сделать такое еще раз
    void BoldSymbol();

    void MakeMapTypeSymbol(int x[][]);  //формирует карту символа с уже имеющейся
  };
  
  //Вспомогательные функции
private:
  {
    int GCx, GCy; //координаты центра тяжести
    int Map[][];  //карта символа
    void LiteMapSymbol();
    void GravityCenter(); 
  };
}

//Облегчаем карту, чтобы сделать значения при вычислении центра тяжести меньше
void FindSymbol::LiteMapSymbol()
{
  for (int i=0; i < this.Map.size; ++i)
    for (int j=0; j < this.Map.size[]; ++j)
      this.Map[i][j] /= 10;
  return;
}

//Центр тяжести данной фигуры
void FindSymbol::GravityCenter()
{
  long int S = 0, mass = 0;
  int GCx, GCy;
  for (int i = 0; i < this.Map.size; ++i)
    {
      long int massRow = 0;
      for (int j = 0; j < this.Map.size; ++j)
	massRow += this.Map[i][j];
      mass += massRow;
      S += massRow * i;
    }
  this.GCy = S / mass;
  S = 0;
  for (int j = 0; j < this.Map.size; ++j)
    {
      long int massColumn = 0;
      for (int i = 0; i < this.Map.size; ++i)
	massColumn += x[i][j];
      S += massColumn * j;
    }
  this.GCx = S / mass;
  return;
}

void FindSymbol::FindSymbol(int x[][])
{
  for (int i = 0; i < x.size; ++i)
    for (int j = 0; j < x.size; ++j)
      this.Map[i][j] = x[i][j];
  this.GCx = 0;
  this.GCy = 0;
}
*/
