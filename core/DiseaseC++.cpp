#include "hadoop/Pipes.hh"
#include "hadoop/TemplateFactory.hh"
#include "hadoop/StringUtils.hh"

#include <algorithm>
#include <limits>
#include <string>
#include <unistd.h>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include  "stdint.h"
 
using namespace std;
 
using namespace std;

class DiseaseApplicationMapper : public HadoopPipes::Mapper
{
  public: DiseaseApplicationMapper( HadoopPipes::TaskContext& context )
  {

  }

  void map( HadoopPipes::MapContext& context )
  {
    
  string line = context.getInputValue();
  string tmp;
    
  string ABCB4[] = {"atg", "gat", "ctt", "gag", "gcg", "gca", "aag", "aac", "gga", "aca", "gcc", "tgg", "cgc", "ccc", "acg", "agc", "gcg", "gag", "ggc", "gac", "ttt", "gaa", "ctg", "ggc", "atc", "agc", "agc", "aaa", "caa", "aaa", "agg", "aaa", "aaa", "acg", "aag", "aca", "gtg", "aaa", "atg", "att", "gga", "gta", "tta", "aca", "ttg", "ttt", "cga", "tac", "tcc", "gat", "tgg", "cag", "gat", "aaa", "ttg", "ttt", "atg", "tcg", "ctg", "ggt", "acc", "atc", "atg", "gcc", "ata", "gct", "cac", "gga", "tca", "ggt", "ctc", "ccc", "ctc", "atg", "atg", "ata", "gta", "ttt", "gga", "gag", "atg", "act", "gac", "aaa", "ttt", "gtt", "gat", "act", "gca", "gga", "aac", "ttc", "tcc", "ttt", "cca", "gtg", "aac", "ttt", "tcc", "ttg", "tcg", "ctg", "cta", "aat", "cca", "ggc", "aaa", "att", "ctg", "gaa", "gaa", "gaa", "atg", "act", "aga", "tat", "gca", "tat", "tac", "tac", "tca", "gga", "ttg", "ggt", "gct", "gga", "gtt", "ctt", "gtt", "gct", "gcc", "tat", "ata", "caa", "gtt", "tca", "ttt", "tgg", "act", "ttg", "gca", "gct", "ggt", "cga", "cag", "atc", "agg", "aaa", "att", "agg", "cag", "aag", "ttt", "ttt", "cat", "gct", "att", "cta", "cga", "cag", "gaa", "ata", "gga", "tgg", "ttt", "gac", "atc", "aac", "gac", "acc", "act", "gaa", "ctc", "aat", "acg", "cgg", "cta", "aca", "gat", "gac", "atc", "tcc", "aaa", "atc", "agt", "gaa", "gga", "att", "ggt", "gac", "aag", "gtt", "gga", "atg", "ttc", "ttt", "caa", "gca", "gta", "gcc", "acg", "ttt", "ttt", "gca", "gga", "ttc", "ata", "gtg", "gga", "ttc", "atc", "aga", "gga", "tgg", "aag", "ctc", "acc", "ctt", "gtg", "ata", "atg", "gcc", "atc", "agc", "cct", "att", "cta", "gga", "ctc", "tct", "gca", "gcc", "gtt", "tgg", "gca", "aag", "ata", "ctc", "tcg", "gca", "ttt", "agt", "gac", "aaa", "gaa", "cta", "gct", "gct", "tat", "gca", "aaa", "gca", "ggc", "gcc", "gtg", "gca", "gaa", "gag", "gct", "ctg", "ggg", "gcc", "atc", "agg", "act", "gtg", "ata", "gct", "ttc", "ggg", "ggc", "cag", "aac", "aaa", "gag", "ctg", "gaa", "agg", "tat", "cag", "aaa", "cat", "tta", "gaa", "aat", "gcc", "aaa", "gag", "att", "gga", "att", "aaa", "aaa", "gct", "att", "tca", "gca", "aac", "att", "tcc", "atg", "ggt", "att", "gcc", "ttc", "ctg", "tta", "ata", "tat", "gca", "tca", "tat", "gca", "ctg", "gcc", "ttc", "tgg", "tat", "gga", "tcc", "act", "cta", "gtc", "ata", "tca", "aaa", "gaa", "tat", "act", "att", "gga", "aat", "gca", "atg", "aca", "gtt", "ttt", "ttt", "tca", "atc", "cta", "att", "gga", "gct", "ttc", "agt", "gtt", "ggc", "cag", "gct", "gcc", "cca", "tgt", "att", "gat", "gct", "ttt", "gcc", "aat", "gca", "aga", "gga", "gca", "gca", "tat", "gtg", "atc", "ttt", "gat", "att", "att", "gat", "aat", "aat", "cct", "aaa", "att", "gac", "agt", "ttt", "tca", "gag", "aga", "gga", "cac", "aaa", "cca", "gac", "agc", "atc", "aaa", "ggg", "aat", "ttg", "gag", "ttc", "aat", "gat", "gtt", "cac", "ttt", "tct", "tac", "cct", "tct", "cga", "gct", "aac", "gtc", "aag", "atc", "ttg", "aag", "ggc", "ctc", "aac", "ctg", "aag", "gtg", "cag", "agt", "ggg", "cag", "acg", "gtg", "gcc", "ctg", "gtt", "gga", "agt", "agt", "ggc", "tgt", "ggg", "aag", "agc", "aca", "acg", "gtc", "cag", "ctg", "ata", "cag", "agg", "ctc", "tat", "gac", "cct", "gat", "gag", "ggc", "aca", "att", "aac", "att", "gat", "ggg", "cag", "gat", "att", "agg", "aac", "ttt", "aat", "gta", "aac", "tat", "ctg", "agg", "gaa", "atc", "att", "ggt", "gtg", "gtg", "agt", "cag", "gag", "ccg", "gtg", "ctg", "ttt", "tcc", "acc", "aca", "att", "gct", "gaa", "aat", "att", "tgt", "tat", "ggc", "cgt", "gga", "aat", "gta", "acc", "atg", "gat", "gag", "ata", "aag", "aaa", "gct", "gtc", "aaa", "gag", "gcc", "aac", "gcc", "tat", "gag", "ttt", "atc", "atg", "aaa", "tta", "cca", "cag", "aaa", "ttt", "gac", "acc", "ctg", "gtt", "gga", "gag", "aga", "ggg", "gcc", "cag", "ctg", "agt", "ggt", "ggg", "cag", "aag", "cag", "agg", "atc", "gcc", "att", "gca", "cgt", "gcc", "ctg", "gtt", "cgc", "aac", "ccc", "aag", "atc", "ctt", "ctg", "ctg", "gat", "gag", "gcc", "acg", "tca", "gca", "ttg", "gac", "aca", "gaa", "agt", "gaa", "gct", "gag", "gta", "cag", "gca", "gct", "ctg", "gat", "aag", "gcc", "aga", "gaa", "ggc", "cgg", "acc", "acc", "att", "gtg", "ata", "gca", "cac", "cga", "ctg", "tct", "acg", "gtc", "cga", "aat", "gca", "gat", "gtc", "atc", "gct", "ggg", "ttt", "gag", "gat", "gga", "gta", "att", "gtg", "gag", "caa", "gga", "agc", "cac", "agc", "gaa", "ctg", "atg", "aag", "aag", "gaa", "ggg", "gtg", "tac", "ttc", "aaa", "ctt", "gtc", "aac", "atg", "cag", "aca", "tca", "gga", "agc", "cag", "atc", "cag", "tca", "gaa", "gaa", "ttt", "gaa", "cta", "aat", "gat", "gaa", "aag", "gct", "gcc", "act", "aga", "atg", "gcc", "cca", "aat", "ggc", "tgg", "aaa", "tct", "cgc", "cta", "ttt", "agg", "cat", "tct", "act", "cag", "aaa", "aac", "ctt", "aaa", "aat", "tca", "caa", "atg", "tgt", "cag", "aag", "agc", "ctt", "gat", "gtg", "gaa", "acc", "gat", "gga", "ctt", "gaa", "gca", "aat", "gtg", "cca", "cca", "gtg", "tcc", "ttt", "ctg", "aag", "gtc", "ctg", "aaa", "ctg", "aat", "aaa", "aca", "gaa", "tgg", "ccc", "tac", "ttt", "gtc", "gtg", "gga", "aca", "gta", "tgt", "gcc", "att", "gcc", "aat", "ggg", "ggg", "ctt", "cag", "ccg", "gca", "ttt", "tca", "gtc", "ata", "ttc", "tca", "gag", "atc", "ata", "gcg", "att", "ttt", "gga", "cca", "ggc", "gat", "gat", "gca", "gtg", "aag", "cag", "cag", "aag", "tgc", "aac", "ata", "ttc", "tct", "ttg", "att", "ttc", "tta", "ttt", "ctg", "gga", "att", "att", "tct", "ttt", "ttt", "act", "ttc", "ttc", "ctt", "cag", "ggt", "ttc", "acg", "ttt", "ggg", "aaa", "gct", "ggc", "gag", "atc", "ctc", "acc", "aga", "aga", "ctg", "cgg", "tca", "atg", "gct", "ttt", "aaa", "gca", "atg", "cta", "aga", "cag", "gac", "atg", "agc", "tgg", "ttt", "gat", "gac", "cat", "aaa", "aac", "agt", "act", "ggt", "gca", "ctt", "tct", "aca", "aga", "ctt", "gcc", "aca", "gat", "gct", "gcc", "caa", "gtc", "caa", "gga", "gcc", "aca", "gga", "acc", "agg", "ttg", "gct", "tta", "att", "gca", "cag", "aat", "ata", "gct", "aac", "ctt", "gga", "act", "ggt", "att", "atc", "ata", "tca", "ttt", "atc", "tac", "ggt", "tgg", "cag", "tta", "acc", "cta", "ttg", "cta", "tta", "gca", "gtt", "gtt", "cca", "att", "att", "gct", "gtg", "tca", "gga", "att", "gtt", "gaa", "atg", "aaa", "ttg", "ttg", "gct", "gga", "aat", "gcc", "aaa", "aga", "gat", "aaa", "aaa", "gaa", "ctg", "gaa", "gct", "gct", "gga", "aag", "att", "gca", "aca", "gag", "gca", "ata", "gaa", "aat", "att", "agg", "aca", "gtt", "gtg", "tct", "ttg", "acc", "cag", "gaa", "aga", "aaa", "ttt", "gaa", "tca", "atg", "tat", "gtt", "gaa", "aaa", "ttg", "tat", "gga", "cct", "tac", "agg", "aat", "tct", "gtg", "cag", "aag", "gca", "cac", "atc", "tat", "gga", "att", "act", "ttt", "agt", "atc", "tca", "caa", "gca", "ttt", "atg", "tat", "ttt", "tcc", "tat", "gcc", "ggt", "tgt", "ttt", "cga", "ttt", "ggt", "gca", "tat", "ctc", "att", "gtg", "aat", "gga", "cat", "atg", "cgc", "ttc", "aga", "gat", "gtt", "att", "ctg", "gtg", "ttt", "tct", "gca", "att", "gta", "ttt", "ggt", "gca", "gtg", "gct", "cta", "gga", "cat", "gcc", "agt", "tca", "ttt", "gct", "cca", "gac", "tat", "gct", "aaa", "gct", "aag", "ctg", "tct", "gca", "gcc", "cac", "tta", "ttc", "atg", "ctg", "ttt", "gaa", "aga", "caa", "cct", "ctg", "att", "gac", "agc", "tac", "agt", "gaa", "gag", "ggg", "ctg", "aag", "cct", "gat", "aaa", "ttt", "gaa", "gga", "aat", "ata", "aca", "ttt", "aat", "gaa", "gtc", "gtg", "ttc", "aac", "tat", "ccc", "acc", "cga", "gca", "aac", "gtg", "cca", "gtg", "ctt", "cag", "ggg", "ctg", "agc", "ctg", "gag", "gtg", "aag", "aaa", "ggc", "cag", "aca", "cta", "gcc", "ctg", "gtg", "ggc", "agc", "agt", "ggc", "tgt", "ggg", "aag", "agc", "acg", "gtg", "gtc", "cag", "ctc", "ctg", "gag", "cgg", "ttc", "tac", "gac", "ccc", "ttg", "gcg", "ggg", "aca", "gtg", "ttt", "gtg", "gac", "ttt", "ggt", "ttt", "cag", "ctt", "ctc", "gat", "ggt", "caa", "gaa", "gca", "aag", "aaa", "ctc", "aat", "gtc", "cag", "tgg", "ctc", "aga", "gct", "caa", "ctc", "gga", "atc", "gtg", "tct", "cag", "gag", "cct", "atc", "cta", "ttt", "gac", "tgc", "agc", "att", "gcc", "gag", "aat", "att", "gcc", "tat", "gga", "gac", "aac", "agc", "cgg", "gtt", "gta", "tca", "cag", "gat", "gaa", "att", "gtg", "agt", "gca", "gcc", "aaa", "gct", "gcc", "aac", "ata", "cat", "cct", "ttc", "atc", "gag", "acg", "tta", "ccc", "cac", "aaa", "tat", "gaa", "aca", "aga", "gtg", "gga", "gat", "aag", "ggg", "act", "cag", "ctc", "tca", "gga", "ggt", "caa", "aaa", "cag", "agg", "att", "gct", "att", "gcc", "cga", "gcc", "ctc", "atc", "aga", "caa", "cct", "caa", "atc", "ctc", "ctg", "ttg", "gat", "gaa", "gct", "aca", "tca", "gct", "ctg", "gat", "act", "gaa", "agt", "gaa", "aag", "gtt", "gtc", "caa", "gaa", "gcc", "ctg", "gac", "aaa", "gcc", "aga", "gaa", "ggc", "cgc", "acc", "tgc", "att", "gtg", "att", "gct", "cac", "cgc", "ctg", "tcc", "acc", "atc", "cag", "aat", "gca", "gac", "tta", "ata", "gtg", "gtg", "ttt", "cag", "aat", "ggg", "aga", "gtc", "aag", "gag", "cat", "ggc", "acg", "cat", "cag", "cag", "ctg", "ctg", "gca", "cag", "aaa", "ggc", "atc", "tat", "ttt", "tca", "atg", "gtc", "agt", "gtc", "cag", "gct", "ggg", "aca", "cag", "aac", "tta"};
	string ABCB11[] = {"atg", "tct", "gac", "tca", "gta", "att", "ctt", "cga", "agt", "ata", "aag", "aaa", "ttt", "gga", "gag", "gag", "aat", "gat", "ggt", "ttt", "gag", "tca", "gat", "aaa", "tca", "tat", "aat", "aat", "gat", "aag", "aaa", "tca", "agg", "tta", "caa", "gat", "gag", "aag", "aaa", "ggt", "gat", "ggc", "gtt", "aga", "gtt", "ggc", "ttc", "ttt", "caa", "ttg", "ttt", "cgg", "ttt", "tct", "tca", "tca", "act", "gac", "att", "tgg", "ctg", "atg", "ttt", "gtg", "gga", "agt", "ttg", "tgt", "gca", "ttt", "ctc", "cat", "gga", "ata", "gcc", "cag", "cca", "ggc", "gtg", "cta", "ctc", "att", "ttt", "ggc", "aca", "atg", "aca", "gat", "gtt", "ttt", "att", "gac", "tac", "gac", "gtt", "gag", "tta", "caa", "gaa", "ctc", "cag", "att", "cca", "gga", "aaa", "gca", "tgt", "gtg", "aat", "aac", "acc", "att", "gta", "tgg", "act", "aac", "agt", "tcc", "ctc", "aac", "cag", "aac", "atg", "aca", "aat", "gga", "aca", "cgt", "tgt", "ggg", "ttg", "ctg", "aac", "atc", "gag", "agc", "gaa", "atg", "atc", "aaa", "ttt", "gcc", "agt", "tac", "tat", "gct", "gga", "att", "gct", "gtc", "gca", "gta", "ctt", "atc", "aca", "gga", "tat", "att", "caa", "ata", "tgc", "ttt", "tgg", "gtc", "att", "gcc", "gca", "gct", "cgt", "cag", "ata", "cag", "aaa", "atg", "aga", "aaa", "ttt", "tac", "ttt", "agg", "aga", "ata", "atg", "aga", "atg", "gaa", "ata", "ggg", "tgg", "ttt", "gac", "tgc", "aat", "tca", "gtg", "ggg", "gag", "ctg", "aat", "aca", "aga", "ttc", "tct", "gat", "gat", "att", "aat", "aaa", "atc", "aat", "gat", "gcc", "ata", "gct", "gac", "caa", "atg", "gcc", "ctt", "ttc", "att", "cag", "cgc", "atg", "acc", "tcg", "acc", "atc", "tgt", "ggt", "ttc", "ctg", "ttg", "gga", "ttt", "ttc", "agg", "ggt", "tgg", "aaa", "ctg", "acc", "ttg", "gtt", "att", "att", "tct", "gtc", "agc", "cct", "ctc", "att", "ggg", "att", "gga", "gca", "gcc", "acc", "att", "ggt", "ctg", "agt", "gtg", "tcc", "aag", "ttt", "acg", "gac", "tat", "gag", "ctg", "aag", "gcc", "tat", "gcc", "aaa", "gca", "ggg", "gtg", "gtg", "gct", "gat", "gaa", "gtc", "att", "tca", "tca", "atg", "aga", "aca", "gtg", "gct", "gct", "ttt", "ggt", "ggt", "gag", "aaa", "aga", "gag", "gtt", "gaa", "agg", "tat", "gag", "aaa", "aat", "ctt", "gtg", "ttc", "gcc", "cag", "cgt", "tgg", "gga", "att", "aga", "aaa", "gga", "ata", "gtg", "atg", "gga", "ttc", "ttt", "act", "gga", "ttc", "gtg", "tgg", "tgt", "ctc", "atc", "ttt", "ttg", "tgt", "tat", "gca", "ctg", "gcc", "ttc", "tgg", "tac", "ggc", "tcc", "aca", "ctt", "gtc", "ctg", "gat", "gaa", "gga", "gaa", "tat", "aca", "cca", "gga", "acc", "ctt", "gtc", "cag", "att", "ttc", "ctc", "agt", "gtc", "ata", "gta", "gga", "gct", "tta", "aat", "ctt", "ggc", "aat", "gcc", "tct", "cct", "tgt", "ttg", "gaa", "gcc", "ttt", "gca", "act", "gga", "cgt", "gca", "gca", "gcc", "acc", "agc", "att", "ttt", "gag", "aca", "ata", "gac", "agg", "aaa", "ccc", "atc", "att", "gac", "tgc", "atg", "tca", "gaa", "gat", "ggt", "tac", "aag", "ttg", "gat", "cga", "atc", "aag", "ggt", "gaa", "att", "gaa", "ttc", "cat", "aat", "gtg", "acc", "ttc", "cat", "tat", "cct", "tcc", "aga", "cca", "gag", "gtg", "aag", "att", "cta", "aat", "gac", "ctc", "aac", "atg", "gtc", "att", "aaa", "cca", "ggg", "gaa", "atg", "aca", "gct", "ctg", "gta", "gga", "ccc", "agt", "gga", "gct", "gga", "aaa", "agt", "aca", "gca", "ctg", "caa", "ctc", "att", "cag", "cga", "ttc", "tat", "gac", "ccc", "tgt", "gaa", "gga", "atg", "gtg", "acc", "gtg", "gat", "ggc", "cat", "gac", "att", "cgc", "tct", "ctt", "aac", "att", "cag", "tgg", "ctt", "aga", "gat", "cag", "att", "ggg", "ata", "gtg", "gag", "caa", "gag", "cca", "gtt", "ctg", "ttc", "tct", "acc", "acc", "att", "gca", "gaa", "aat", "att", "cgc", "tat", "ggc", "aga", "gaa", "gat", "gca", "aca", "atg", "gaa", "gac", "ata", "gtc", "caa", "gct", "gcc", "aag", "gag", "gcc", "aat", "gcc", "tac", "aac", "ttc", "atc", "atg", "gac", "ctg", "cca", "cag", "caa", "ttt", "gac", "acc", "ctt", "gtt", "gga", "gaa", "gga", "gga", "ggc", "cag", "atg", "agt", "ggt", "ggc", "cag", "aaa", "caa", "agg", "gta", "gct", "atc", "gcc", "aga", "gcc", "ctc", "atc", "cga", "aat", "ccc", "aag", "att", "ctg", "ctt", "ttg", "gac", "atg", "gcc", "acc", "tca", "gct", "ctg", "gac", "aat", "gag", "agt", "gaa", "gcc", "atg", "gtg", "caa", "gaa", "gtg", "ctg", "agt", "aag", "att", "cag", "cat", "ggg", "cac", "aca", "atc", "att", "tca", "gtt", "gct", "cat", "cgc", "ttg", "tct", "acg", "gtc", "aga", "gct", "gca", "gat", "acc", "atc", "att", "ggt", "ttt", "gaa", "cat", "ggc", "act", "gca", "gtg", "gaa", "aga", "ggg", "acc", "cat", "gaa", "gaa", "tta", "ctg", "gaa", "agg", "aaa", "ggt", "gtt", "tac", "ttc", "act", "cta", "gtg", "act", "ttg", "caa", "agc", "cag", "gga", "aat", "caa", "gct", "ctt", "aat", "gaa", "gag", "gac", "ata", "aag", "gat", "gca", "act", "gaa", "gat", "gac", "atg", "ctt", "gcg", "agg", "acc", "ttt", "agc", "aga", "ggg", "agc", "tac", "cag", "gat", "agt", "tta", "agg", "gct", "tcc", "atc", "cgg", "caa", "cgc", "tcc", "aag", "tct", "cag", "ctt", "tct", "tac", "ctg", "gtg", "cac", "gaa", "cct", "cca", "tta", "gct", "gtt", "gta", "gat", "cat", "aag", "tct", "acc", "tat", "gaa", "gaa", "gat", "aga", "aag", "gac", "aag", "gac", "att", "cct", "gtg", "cag", "gaa", "gaa", "gtt", "gaa", "cct", "gcc", "cca", "gtt", "agg", "agg", "att", "ctg", "aaa", "ttc", "agt", "gct", "cca", "gaa", "tgg", "ccc", "tac", "atg", "ctg", "gta", "ggg", "tct", "gtg", "ggt", "gca", "gct", "gtg", "aac", "ggg", "aca", "gtc", "aca", "ccc", "ttg", "tat", "gcc", "ttt", "tta", "ttc", "agc", "cag", "att", "ctt", "ggg", "act", "ttt", "tca", "att", "cct", "gat", "aaa", "gag", "gaa", "caa", "agg", "tca", "cag", "atc", "aat", "ggt", "gtg", "tgc", "cta", "ctt", "ttt", "gta", "gca", "atg", "ggc", "tgt", "gta", "tct", "ctt", "ttc", "acc", "caa", "ttt", "cta", "cag", "gga", "tat", "gcc", "ttt", "gct", "aaa", "tct", "ggg", "gag", "ctc", "cta", "aca", "aaa", "agg", "cta", "cgt", "aaa", "ttt", "ggt", "ttc", "agg", "gca", "atg", "ctg", "ggg", "caa", "gat", "att", "gcc", "tgg", "ttt", "gat", "gac", "ctc", "aga", "aat", "agc", "cct", "gga", "gca", "ttg", "aca", "aca", "aga", "ctt", "gct", "aca", "gat", "gct", "tcc", "caa", "gtt", "caa", "ggg", "gct", "gcc", "ggc", "tct", "cag", "atc", "ggg", "atg", "ata", "gtc", "aat", "tcc", "ttc", "act", "aac", "gtc", "act", "gtg", "gcc", "atg", "atc", "att", "gcc", "ttc", "tcc", "ttt", "agc", "tgg", "aag", "ctg", "agc", "ctg", "gtc", "atc", "ttg", "tgc", "ttc", "ttc", "ccc", "ttc", "ttg", "gct", "tta", "tca", "gga", "gcc", "aca", "cag", "acc", "agg", "atg", "ttg", "aca", "gga", "ttt", "gcc", "tct", "cga", "gat", "aag", "cag", "gcc", "ctg", "gag", "atg", "gtg", "gga", "cag", "att", "aca", "aat", "gaa", "gcc", "ctc", "agt", "aac", "atc", "cgc", "act", "gtt", "gct", "gga", "att", "gga", "aag", "gag", "agg", "cgg", "ttc", "att", "gaa", "gca", "ctt", "gag", "act", "gag", "ctg", "gag", "aag", "ccc", "ttc", "aag", "aca", "gcc", "att", "cag", "aaa", "gcc", "aat", "att", "tac", "gga", "ttc", "tgc", "ttt", "gcc", "ttt", "gcc", "cag", "tgc", "atc", "atg", "ttt", "att", "gcg", "aat", "tct", "gct", "tcc", "tac", "aga", "tat", "gga", "ggt", "tac", "tta", "atc", "tcc", "aat", "gag", "ggg", "ctc", "cat", "ttc", "agc", "tat", "gtg", "ttc", "agg", "gtg", "atc", "tct", "gca", "gtt", "gta", "ctg", "agt", "gca", "aca", "gct", "ctt", "gga", "aga", "gcc", "ttc", "tct", "tac", "acc", "cca", "agt", "tat", "gca", "aaa", "gct", "aaa", "ata", "tca", "gct", "gca", "cgc", "ttt", "ttt", "caa", "ctg", "ctg", "gac", "cga", "caa", "ccc", "cca", "atc", "agt", "gta", "tac", "aat", "act", "gca", "ggt", "gaa", "aaa", "tgg", "gac", "aac", "ttc", "cag", "ggg", "aag", "att", "gat", "ttt", "gtt", "gat", "tgt", "aaa", "ttt", "aca", "tat", "cct", "tct", "cga", "cct", "gac", "tcg", "caa", "gtt", "ctg", "aat", "ggt", "ctc", "tca", "gtg", "tcg", "att", "agt", "cca", "ggg", "cag", "aca", "ctg", "gcg", "ttt", "gtt", "ggg", "agc", "agt", "gga", "tgt", "ggc", "aaa", "agc", "act", "agc", "att", "cag", "ctg", "ttg", "gaa", "cgt", "ttc", "tat", "gat", "cct", "gat", "caa", "ggg", "aag", "gtg", "atg", "ata", "gat", "ggt", "cat", "gac", "agc", "aaa", "aaa", "gta", "aat", "gtc", "cag", "ttc", "ctc", "cgc", "tca", "aac", "att", "gga", "att", "gtt", "tcc", "cag", "gaa", "cca", "gtg", "ttg", "ttt", "gcc", "tgt", "agc", "ata", "atg", "gac", "aat", "atc", "aag", "tat", "gga", "gac", "aac", "acc", "aaa", "gaa", "att", "ccc", "atg", "gaa", "aga", "gtc", "ata", "gca", "gct", "gca", "aaa", "cag", "gct", "cag", "ctg", "cat", "gat", "ttt", "gtc", "atg", "tca", "ctc", "cca", "gag", "aaa", "tat", "gaa", "act", "aac", "gtt", "ggg", "tcc", "cag", "ggg", "tct", "caa", "ctc", "tct", "aga", "ggg", "gag", "aaa", "caa", "cgc", "att", "gct", "att", "gct", "cgg", "gcc", "att", "gta", "cga", "gat", "cct", "aaa", "atc", "ttg", "cta", "cta", "gat", "gaa", "gcc", "act", "tct", "gcc", "tta", "gac", "aca", "gaa", "agt", "gaa", "aag", "acg", "gtg", "cag", "gtt", "gct", "cta", "gac", "aaa", "gcc", "aga", "gag", "ggt", "cgg", "acc", "tgc", "att", "gtc", "att", "gcc", "cat", "cgc", "ttg", "tcc", "acc", "atc", "cag", "aac", "gcg", "gat", "atc", "att", "gct", "gtc", "atg", "gca", "cag", "ggg", "gtg", "gtg", "att", "gaa", "aag", "ggg", "acc", "cat", "gaa", "gaa", "ctg", "atg", "gcc", "caa", "aaa", "gga", "gcc", "tac", "tac", "aaa", "cta", "gtc", "acc", "act", "gga", "tcc", "ccc", "atc", "agt"};
	string ATP8B1[] = {"atg", "agt", "aca", "gaa", "aga", "gac", "tca", "gaa", "acg", "aca", "ttt", "gac", "gag", "gat", "tct", "cag", "cct", "aat", "gac", "gaa", "gtg", "gtt", "ccc", "tac", "agt", "gat", "gat", "gaa", "aca", "gaa", "gat", "gaa", "ctt", "gat", "gac", "cag", "ggg", "tct", "gct", "gtt", "gaa", "cca", "gaa", "caa", "aac", "cga", "gtc", "aac", "agg", "gaa", "gca", "gag", "gag", "aac", "cgg", "gag", "cca", "ttc", "aga", "aaa", "gaa", "tgt", "aca", "tgg", "caa", "gtc", "aaa", "gca", "aac", "gat", "cgc", "aag", "tac", "cac", "gaa", "caa", "cct", "cac", "ttt", "atg", "aac", "aca", "aaa", "ttc", "ttg", "tgt", "att", "aag", "gag", "agt", "aaa", "tat", "gcg", "aat", "aat", "gca", "att", "aaa", "aca", "tac", "aag", "tac", "aac", "gca", "ttt", "acc", "ttt", "ata", "cca", "atg", "aat", "ctg", "ttt", "gag", "cag", "ttt", "aag", "aga", "gca", "gcc", "aat", "tta", "tat", "ttc", "ctg", "gct", "ctt", "ctt", "atc", "tta", "cag", "gca", "gtt", "cct", "caa", "atc", "tct", "acc", "ctg", "gct", "tgg", "tac", "acc", "aca", "cta", "gtg", "ccc", "ctg", "ctt", "gtg", "gtg", "ctg", "ggc", "gtc", "act", "gca", "atc", "aaa", "gac", "ctg", "gtg", "gac", "gat", "gtg", "gct", "cgc", "cat", "aaa", "atg", "gat", "aag", "gaa", "atc", "aac", "aat", "agg", "acg", "tgt", "gaa", "gtc", "att", "aag", "gat", "ggc", "agg", "ttc", "aaa", "gtt", "gct", "aag", "tgg", "aaa", "gaa", "att", "caa", "gtt", "gga", "gac", "gtc", "att", "cgt", "ctg", "aaa", "aaa", "aat", "gat", "ttt", "gtt", "cca", "gct", "gac", "att", "ctc", "ctg", "ctg", "tct", "agc", "tct", "gag", "cct", "aac", "agc", "ctc", "tgc", "tat", "gtg", "gaa", "aca", "gca", "gaa", "ctg", "gat", "gga", "gaa", "acc", "aat", "tta", "aaa", "ttt", "aag", "atg", "tca", "ctt", "gaa", "atc", "aca", "gac", "cag", "tac", "ctc", "caa", "aga", "gaa", "gat", "aca", "ttg", "gct", "aca", "ttt", "gat", "ggt", "ttt", "att", "gaa", "tgt", "gaa", "gaa", "ccc", "aat", "aac", "aga", "cta", "gat", "aag", "ttt", "aca", "gga", "aca", "cta", "ttt", "tgg", "aga", "aac", "aca", "agt", "ttt", "cct", "ttg", "gat", "gct", "gat", "aaa", "att", "ttg", "tta", "cgt", "ggc", "tgt", "gta", "att", "agg", "aac", "acc", "gat", "ttc", "tgc", "cac", "ggc", "tta", "gtc", "att", "ttt", "gca", "ggt", "gct", "gac", "act", "aaa", "ata", "atg", "aag", "aat", "agt", "ggg", "aaa", "acc", "aga", "ttt", "aaa", "aga", "act", "aaa", "att", "gat", "tac", "ttg", "atg", "aac", "tac", "atg", "gtt", "tac", "acg", "atc", "ttt", "gtt", "gtt", "ctt", "att", "ctg", "ctt", "tct", "gct", "ggt", "ctt", "gcc", "atc", "ggc", "cat", "gct", "tat", "tgg", "gaa", "gca", "cag", "gtg", "ggc", "aat", "tcc", "tct", "tgg", "tac", "ctc", "tat", "gat", "gga", "gaa", "gac", "gat", "aca", "ccc", "tcc", "tac", "cgt", "gga", "ttc", "ctc", "att", "ttc", "tgg", "ggc", "tat", "atc", "att", "gtt", "ctc", "aac", "acc", "atg", "gta", "ccc", "atc", "tct", "ctc", "tat", "gtc", "agc", "gtg", "gaa", "gtg", "att", "cgt", "ctt", "gga", "cag", "agt", "cac", "ttc", "atc", "aac", "tgg", "gac", "ctg", "caa", "atg", "tac", "tat", "gct", "gag", "aag", "gac", "aca", "ccc", "gca", "aaa", "gct", "aga", "acc", "acc", "aca", "ctc", "aat", "gaa", "cag", "ctc", "ggg", "cag", "atc", "cat", "tat", "atc", "ttc", "tct", "gat", "aag", "acg", "ggg", "aca", "ctc", "aca", "caa", "aat", "atc", "atg", "acc", "ttt", "aaa", "aag", "tgc", "tgt", "atc", "aac", "ggg", "cag", "ata", "tat", "ggg", "gac", "cat", "cgg", "gat", "gcc", "tct", "caa", "cac", "aac", "cac", "aac", "aaa", "ata", "gag", "caa", "gtt", "gat", "ttt", "agc", "tgg", "aat", "aca", "tat", "gct", "gat", "ggg", "aag", "ctt", "gca", "ttt", "tat", "gac", "cac", "tat", "ctt", "att", "gag", "caa", "atc", "cag", "tca", "ggg", "aaa", "gag", "cca", "gaa", "gta", "cga", "cag", "ttc", "ttc", "ttc", "ttg", "ctc", "gca", "gtt", "tgc", "cac", "aca", "gtc", "atg", "gtg", "gat", "agg", "act", "gat", "ggt", "cag", "ctc", "aac", "tac", "cag", "gca", "gcc", "tct", "ccc", "gat", "gaa", "ggt", "gcc", "ctg", "gta", "aac", "gct", "gcc", "agg", "aac", "ttt", "ggc", "ttt", "gcc", "ttc", "ctc", "gcc", "agg", "acc", "cag", "aac", "acc", "atc", "acc", "atc", "agt", "gaa", "ctg", "ggc", "act", "gaa", "agg", "act", "tac", "aat", "gtt", "ctt", "gcc", "att", "ttg", "gac", "ttc", "aac", "agt", "gac", "cgg", "aag", "cga", "atg", "tct", "atc", "att", "gta", "aga", "acc", "cca", "gaa", "ggc", "aat", "atc", "aag", "ctt", "tac", "tgt", "aaa", "ggt", "gct", "gac", "act", "gtt", "att", "tat", "gaa", "cgg", "tta", "cat", "cga", "atg", "aat", "cct", "act", "aag", "caa", "gaa", "aca", "cag", "gat", "gcc", "ctg", "gat", "atc", "ttt", "gca", "aat", "gaa", "act", "ctt", "aga", "acc", "cta", "tgc", "ctt", "tgc", "tac", "aag", "gaa", "att", "gaa", "gaa", "aaa", "gaa", "ttt", "aca", "gaa", "tgg", "aat", "aaa", "aag", "ttt", "atg", "gct", "gcc", "agt", "gtg", "gcc", "tcc", "acc", "aac", "cgg", "gac", "gaa", "gct", "ctg", "gat", "aaa", "gta", "tat", "gag", "gag", "att", "gaa", "aaa", "gac", "tta", "att", "ctc", "ctg", "gga", "gct", "aca", "gct", "att", "gaa", "gac", "aag", "cta", "cag", "gat", "gga", "gtt", "cca", "gaa", "acc", "att", "tca", "aaa", "ctt", "gca", "aaa", "gct", "gac", "att", "aag", "atc", "tgg", "gtg", "ctt", "act", "gga", "gac", "aaa", "aag", "gaa", "act", "gct", "gaa", "aat", "ata", "gga", "ttt", "gct", "tgt", "gaa", "ctt", "ctg", "act", "gaa", "gac", "acc", "acc", "atc", "tgc", "tat", "ggg", "gag", "gat", "att", "aat", "tct", "ctt", "ctt", "cat", "gca", "agg", "atg", "gaa", "aac", "cag", "agg", "aat", "aga", "ggt", "ggc", "gtc", "tac", "gca", "aag", "ttt", "gca", "cct", "cct", "gtg", "cag", "gaa", "tct", "ttt", "ttt", "cca", "ccc", "ggt", "gga", "aac", "cgt", "gcc", "tta", "atc", "atc", "act", "ggt", "tct", "tgg", "ttg", "aat", "gaa", "att", "ctt", "ctc", "gag", "aaa", "aag", "acc", "aag", "aga", "aat", "aag", "att", "ctg", "aag", "ctg", "aag", "ttc", "cca", "aga", "aca", "gaa", "gaa", "gaa", "aga", "cgg", "atg", "cgg", "acc", "caa", "agt", "aaa", "agg", "agg", "cta", "gaa", "gct", "aag", "aaa", "gag", "cag", "cgg", "cag", "aaa", "aac", "ttt", "gtg", "gac", "ctg", "gcc", "tgc", "gag", "tgc", "agc", "gca", "gtc", "atc", "tgc", "tgc", "cgc", "gtc", "acc", "ccc", "aag", "cag", "aag", "gcc", "atg", "gtg", "gtg", "gac", "ctg", "gtg", "aag", "agg", "tac", "aag", "aaa", "gcc", "atc", "acg", "ctg", "gcc", "atc", "gga", "gat", "ggg", "gcc", "aat", "gac", "gtg", "aac", "atg", "atc", "aaa", "act", "gcc", "cac", "att", "ggc", "gtt", "gga", "ata", "agt", "gga", "caa", "gaa", "gga", "atg", "caa", "gct", "gtc", "atg", "tcg", "agt", "gac", "tat", "tcc", "ttt", "gct", "cag", "ttc", "cga", "tat", "ctg", "cag", "agg", "cta", "ctg", "ctg", "gtg", "cat", "ggc", "cga", "tgg", "tct", "tac", "ata", "agg", "atg", "tgc", "aag", "ttc", "cta", "cga", "tac", "ttc", "ttt", "tac", "aaa", "aac", "ttt", "gcc", "ttt", "act", "ttg", "gtt", "cat", "ttc", "tgg", "tac", "tcc", "ttc", "ttc", "aat", "ggc", "tac", "tct", "gcg", "cag", "act", "gca", "tac", "gag", "gat", "tgg", "ttc", "atc", "acc", "ctc", "tac", "aac", "gtg", "ctg", "tac", "acc", "agc", "ctg", "ccc", "gtg", "ctc", "ctc", "atg", "ggg", "ctg", "ctc", "gac", "cag", "gat", "gtg", "agt", "gac", "aaa", "ctg", "agc", "ctc", "cga", "ttc", "cct", "ggg", "tta", "tac", "ata", "gtg", "gga", "caa", "aga", "gac", "tta", "cta", "ttc", "aac", "tat", "aag", "aga", "ttc", "ttt", "gta", "agc", "ttg", "ttg", "cat", "ggg", "gtc", "cta", "aca", "tcg", "atg", "atc", "ctc", "ttc", "ttc", "ata", "cct", "ctt", "gga", "gct", "tat", "ctg", "caa", "acc", "gta", "ggg", "cag", "gat", "gga", "gag", "gca", "cct", "tcc", "gac", "tac", "cag", "tct", "ttt", "gcc", "gtc", "acc", "att", "gcc", "tct", "gct", "ctt", "gta", "ata", "aca", "gtc", "aat", "ttc", "cag", "att", "ggc", "ttg", "gat", "act", "tct", "tat", "tgg", "act", "ttt", "gtg", "aat", "gct", "ttt", "tca", "att", "ttt", "gga", "agc", "att", "gca", "ctt", "tat", "ttt", "ggc", "atc", "atg", "ttt", "gac", "ttt", "cat", "agt", "gct", "gga", "ata", "cat", "gtt", "ctc", "ttt", "cca", "tct", "gca", "ttt", "caa", "ttt", "aca", "ggc", "aca", "gct", "tca", "aac", "gct", "ctg", "aga", "cag", "cca", "tac", "att", "tgg", "tta", "act", "atc", "atc", "ctg", "gct", "gtt", "gct", "gtg", "tgc", "tta", "cta", "ccc", "gtc", "gtt", "gcc", "att", "cga", "ttc", "ctg", "tca", "atg", "acc", "atc", "tgg", "cca", "tca", "gaa", "agt", "gat", "aag", "atc", "cag", "aag", "cat", "cgc", "aag", "cgg", "ttg", "aag", "gcg", "gag", "gag", "cag", "tgg", "cag", "cga", "cgg", "cag", "cag", "gtg", "ttc", "cgc", "cgg", "ggc", "gtg", "tca", "acg", "cgg", "cgc", "tcg", "gcc", "tac", "gcc", "ttc", "tcg", "cac", "cag", "cgg", "ggc", "tac", "gcg", "gac", "ctc", "atc", "tcc", "tcc", "ggg", "cgc", "agc", "atc", "cgc", "aag", "aag", "cgc", "tcg", "ccg", "ctt", "gat", "gcc", "atc", "gtg", "gcg", "gat", "ggc", "acc", "gcg", "gag", "tac", "agg", "cgc", "acc", "ggg", "gac", "agc"};
	string JAG1[] =  {"atg", "cgt", "tcc", "cca", "cgg", "acg", "cgc", "ggc", "cgg", "tcc", "ggg", "cgc", "ccc", "cta", "agc", "ctc", "ctg", "ctc", "gcc", "ctg", "ctc", "tgt", "gcc", "ctg", "cga", "gcc", "aag", "gtg", "tgt", "ggg", "gcc", "tcg", "ggt", "cag", "ttc", "gag", "ttg", "gag", "atc", "ctg", "tcc", "atg", "cag", "aac", "gtg", "aac", "ggg", "gag", "ctg", "cag", "aac", "ggg", "aac", "tgc", "tgc", "ggc", "ggc", "gcc", "cgg", "aac", "ccg", "gga", "gac", "cgc", "aag", "tgc", "acc", "cgc", "gac", "gag", "tgt", "gac", "aca", "tac", "ttc", "aaa", "gtg", "tgc", "ctc", "aag", "gag", "tat", "cag", "tcc", "cgc", "gtc", "acg", "gcc", "ggg", "ggg", "ccc", "tgc", "agc", "ttc", "ggc", "tca", "ggg", "tcc", "acg", "cct", "gtc", "atc", "ggg", "ggc", "aac", "acc", "ttc", "aac", "ctc", "aag", "gcc", "agc", "cgc", "ggc", "aac", "gac", "cgc", "aac", "cgc", "atc", "gtg", "ctg", "cct", "ttc", "agt", "ttc", "gcc", "tgg", "ccg", "agg", "tcc", "tat", "acg", "ttg", "ctt", "gtg", "gag", "gcg", "tgg", "gat", "tcc", "agt", "aat", "gac", "acc", "gtt", "caa", "cct", "gac", "agt", "att", "att", "gaa", "aag", "gct", "tct", "cac", "tcg", "ggc", "atg", "atc", "aac", "ccc", "agc", "cgg", "cag", "tgg", "cag", "acg", "ctg", "aag", "cag", "aac", "acg", "ggc", "gtt", "gcc", "cac", "ttt", "gag", "tat", "cag", "atc", "cgc", "gtg", "acc", "tgt", "gat", "gac", "tac", "tac", "tat", "ggc", "ttt", "ggc", "tgc", "aat", "aag", "ttc", "tgc", "cgc", "ccc", "aga", "gat", "gac", "ttc", "ttt", "gga", "cac", "tat", "gcc", "tgt", "gac", "cag", "aat", "ggc", "aac", "aaa", "act", "tgc", "atg", "gaa", "ggc", "tgg", "atg", "ggc", "ccc", "gaa", "tgt", "aac", "aga", "gct", "att", "tgc", "cga", "caa", "ggc", "tgc", "agt", "cct", "aag", "cat", "ggg", "tct", "tgc", "aaa", "ctc", "cca", "ggt", "gac", "tgc", "agg", "tgc", "cag", "tac", "ggc", "tgg", "caa", "ggc", "ctg", "tac", "tgt", "gat", "aag", "tgc", "atc", "cca", "cac", "ccg", "gga", "tgc", "gtc", "cac", "ggc", "atc", "tgt", "aat", "gag", "ccc", "tgg", "cag", "tgc", "ctc", "tgt", "gag", "acc", "aac", "tgg", "ggc", "ggc", "cag", "ctc", "tgt", "gac", "aaa", "gat", "ctc", "aat", "tac", "tgt", "ggg", "act", "cat", "cag", "ccg", "tgt", "ctc", "aac", "ggg", "gga", "act", "tgt", "agc", "aac", "aca", "ggc", "cct", "gac", "aaa", "tat", "cag", "tgt", "tcc", "tgc", "cct", "gag", "ggg", "tat", "tca", "gga", "ccc", "aac", "tgt", "gaa", "att", "gct", "gag", "cac", "gcc", "tgc", "ctc", "tct", "gat", "ccc", "tgt", "cac", "aac", "aga", "ggc", "agc", "tgt", "aag", "gag", "acc", "tcc", "ctg", "ggc", "ttt", "gag", "tgt", "gag", "tgt", "tcc", "cca", "ggc", "tgg", "acc", "ggc", "ccc", "aca", "tgc", "tct", "aca", "aac", "att", "gat", "gac", "tgt", "tct", "cct", "aat", "aac", "tgt", "tcc", "cac", "ggg", "ggc", "acc", "tgc", "cag", "gac", "ctg", "gtt", "aac", "gga", "ttt", "aag", "tgt", "gtg", "tgc", "ccc", "cca", "cag", "tgg", "act", "ggg", "aaa", "acg", "tgc", "cag", "tta", "gat", "gca", "aat", "gaa", "tgt", "gag", "gcc", "aaa", "cct", "tgt", "gta", "aac", "gcc", "aaa", "tcc", "tgt", "aag", "aat", "ctc", "att", "gcc", "agc", "tac", "tac", "tgc", "gac", "tgt", "ctt", "ccc", "ggc", "tgg", "atg", "ggt", "cag", "aat", "tgt", "gac", "ata", "aat", "att", "aat", "gac", "tgc", "ctt", "ggc", "cag", "tgt", "cag", "aat", "gac", "gcc", "tcc", "tgt", "cgg", "gat", "ttg", "gtt", "aat", "ggt", "tat", "cgc", "tgt", "atc", "tgt", "cca", "cct", "ggc", "tat", "gca", "ggc", "gat", "cac", "tgt", "gag", "aga", "gac", "atc", "gat", "gaa", "tgt", "gcc", "agc", "aac", "ccc", "tgt", "ttg", "aat", "ggg", "ggt", "cac", "tgt", "cag", "aat", "gaa", "atc", "aac", "aga", "ttc", "cag", "tgt", "ctg", "tgt", "ccc", "act", "ggt", "ttc", "tct", "gga", "aac", "ctc", "tgt", "cag", "ctg", "gac", "atc", "gat", "tat", "tgt", "gag", "cct", "aat", "ccc", "tgc", "cag", "aac", "ggt", "gcc", "cag", "tgc", "tac", "aac", "cgt", "gcc", "agt", "gac", "tat", "ttc", "tgc", "aag", "tgc", "ccc", "gag", "gac", "tat", "gag", "ggc", "aag", "aac", "tgc", "tca", "cac", "ctg", "aaa", "gac", "cac", "tgc", "cgc", "acg", "acc", "ccc", "tgt", "gaa", "gtg", "att", "gac", "agc", "tgc", "aca", "gtg", "gcc", "atg", "gct", "tcc", "aac", "gac", "aca", "cct", "gaa", "ggg", "gtg", "cgg", "tat", "att", "tcc", "tcc", "aac", "gtc", "tgt", "ggt", "cct", "cac", "ggg", "aag", "tgc", "aag", "agt", "cag", "tcg", "gga", "ggc", "aaa", "ttc", "acc", "tgt", "gac", "tgt", "aac", "aaa", "ggc", "ttc", "acg", "gga", "aca", "tac", "tgc", "cat", "gaa", "aat", "att", "aat", "gac", "tgt", "gag", "agc", "aac", "cct", "tgt", "aga", "aac", "ggt", "ggc", "act", "tgc", "atc", "gat", "ggt", "gtc", "aac", "tcc", "tac", "aag", "tgc", "atc", "tgt", "agt", "gac", "ggc", "tgg", "gag", "ggg", "gcc", "tac", "tgt", "gaa", "acc", "aat", "att", "aat", "gac", "tgc", "agc", "cag", "aac", "ccc", "tgc", "cac", "aat", "ggg", "ggc", "acg", "tgt", "cgc", "gac", "ctg", "gtc", "aat", "gac", "ttc", "tac", "tgt", "gac", "tgt", "aaa", "aat", "ggg", "tgg", "aaa", "gga", "aag", "acc", "tgc", "cac", "tca", "cgt", "gac", "agt", "cag", "tgt", "gat", "gag", "gcc", "acg", "tgc", "aac", "aac", "ggt", "ggc", "acc", "tgc", "tat", "gat", "gag", "ggg", "gat", "gct", "ttt", "aag", "tgc", "atg", "tgt", "cct", "ggc", "ggc", "tgg", "gaa", "gga", "aca", "acc", "tgt", "aac", "ata", "gcc", "cga", "aac", "agt", "agc", "tgc", "ctg", "ccc", "aac", "ccc", "tgc", "cat", "aat", "ggg", "ggc", "aca", "tgt", "gtg", "gtc", "aac", "ggc", "gag", "tcc", "ttt", "acg", "tgc", "gtc", "tgc", "aag", "gaa", "ggc", "tgg", "gag", "ggg", "ccc", "atc", "tgt", "gct", "cag", "aat", "acc", "aat", "gac", "tgc", "agc", "cct", "cat", "ccc", "tgt", "tac", "aac", "agc", "ggc", "acc", "tgt", "gtg", "gat", "gga", "gac", "aac", "tgg", "tac", "cgg", "tgc", "gaa", "tgt", "gcc", "ccg", "ggt", "ttt", "gct", "ggg", "ccc", "gac", "tgc", "aga", "ata", "aac", "atc", "aat", "gaa", "tgc", "cag", "tct", "tca", "cct", "tgt", "gcc", "ttt", "gga", "gcg", "acc", "tgt", "gtg", "gat", "gag", "atc", "aat", "ggc", "tac", "cgg", "tgt", "gtc", "tgc", "cct", "cca", "ggg", "cac", "agt", "ggt", "gcc", "aag", "tgc", "cag", "gaa", "gtt", "tca", "ggg", "aga", "cct", "tgc", "atc", "acc", "atg", "ggg", "agt", "gtg", "ata", "cca", "gat", "ggg", "gcc", "aaa", "tgg", "gat", "gat", "gac", "tgt", "aat", "acc", "tgc", "cag", "tgc", "ctg", "aat", "gga", "cgg", "atc", "gcc", "tgc", "tca", "aag", "gtc", "tgg", "tgt", "ggc", "cct", "cga", "cct", "tgc", "ctg", "ctc", "cac", "aaa", "ggg", "cac", "agc", "gag", "tgc", "ccc", "agc", "ggg", "cag", "agc", "tgc", "atc", "ccc", "atc", "ctg", "gac", "gac", "cag", "tgc", "ttc", "gtc", "cac", "ccc", "tgc", "act", "ggt", "gtg", "ggc", "gag", "tgt", "cgg", "tct", "tcc", "agt", "ctc", "cag", "ccg", "gtg", "aag", "aca", "aag", "tgc", "acc", "tct", "gac", "tcc", "tat", "tac", "cag", "gat", "aac", "tgt", "gcg", "aac", "atc", "aca", "ttt", "acc", "ttt", "aac", "aag", "gag", "atg", "atg", "tca", "cca", "ggt", "ctt", "act", "acg", "gag", "cac", "att", "tgc", "agt", "gaa", "ttg", "agg", "aat", "ttg", "aat", "att", "ttg", "aag", "aat", "gtt", "tcc", "gct", "gaa", "tat", "tca", "atc", "tac", "atc", "gct", "tgc", "gag", "cct", "tcc", "cct", "tca", "gcg", "aac", "aat", "gaa", "ata", "cat", "gtg", "gcc", "att", "tct", "gct", "gaa", "gat", "ata", "cgg", "gat", "gat", "ggg", "aac", "ccg", "atc", "aag", "gaa", "atc", "act", "gac", "aaa", "ata", "atc", "gat", "ctt", "gtt", "agt", "aaa", "cgt", "gat", "gga", "aac", "agc", "tcg", "ctg", "att", "gct", "gcc", "gtt", "gca", "gaa", "gta", "aga", "gtt", "cag", "agg", "cgg", "cct", "ctg", "aag", "aac", "aga", "aca", "gat", "ttc", "ctt", "gtt", "ccc", "ttg", "ctg", "agc", "tct", "gtc", "tta", "act", "gtg", "gct", "tgg", "atc", "tgt", "tgc", "ttg", "gtg", "acg", "gcc", "ttc", "tac", "tgg", "tgc", "ctg", "cgg", "aag", "cgg", "cgg", "aag", "ccg", "ggc", "agc", "cac", "aca", "cac", "tca", "gcc", "tct", "gag", "gac", "aac", "acc", "acc", "aac", "aac", "gtg", "cgg", "gag", "cag", "ctg", "aac", "cag", "atc", "aaa", "aac", "ccc", "att", "gag", "aaa", "cat", "ggg", "gcc", "aac", "acg", "gtc", "ccc", "atc", "aag", "gat", "tat", "gag", "aac", "aag", "aac", "tcc", "aaa", "atg", "tct", "aaa", "ata", "agg", "aca", "cac", "aat", "tct", "gaa", "gta", "gaa", "gag", "gac", "gac", "atg", "gac", "aaa", "cac", "cag", "cag", "aaa", "gcc", "cgg", "ttt", "gcc", "aag", "cag", "ccg", "gcg", "tac", "acg", "ctg", "gta", "gac", "aga", "gaa", "gag", "aag", "ccc", "ccc", "aac", "ggc", "acg", "ccg", "aca", "aaa", "cac", "cca", "aac", "tgg", "aca", "aac", "aaa", "cag", "gac", "aac", "aga", "gac", "ttg", "gaa", "agt", "gcc", "cag", "agc", "tta", "aac", "cga", "atg", "gag", "tac", "atc", "gta"};
	string SERPINA1[] = {"atg", "ccg", "tct", "tct", "gtc", "tcg", "tgg", "ggc", "atc", "ctc", "ctg", "ctg", "gca", "ggc", "ctg", "tgc", "tgc", "ctg", "gtc", "cct", "gtc", "tcc", "ctg", "gct", "gag", "gat", "ccc", "cag", "gga", "gat", "gct", "gcc", "cag", "aag", "aca", "gat", "aca", "tcc", "cac", "cat", "gat", "cag", "gat", "cac", "cca", "acc", "ttc", "aac", "aag", "atc", "acc", "ccc", "aac", "ctg", "gct", "gag", "ttc", "gcc", "ttc", "agc", "cta", "tac", "cgc", "cag", "ctg", "gca", "cac", "cag", "tcc", "aac", "agc", "acc", "aat", "atc", "ttc", "ttc", "tcc", "cca", "gtg", "agc", "atc", "gct", "aca", "gcc", "ttt", "gca", "atg", "ctc", "tcc", "ctg", "ggg", "acc", "aag", "gct", "gac", "act", "cac", "gat", "gaa", "atc", "ctg", "gag", "ggc", "ctg", "aat", "ttc", "aac", "ctc", "acg", "gag", "att", "ccg", "gag", "gct", "cag", "atc", "cat", "gaa", "ggc", "ttc", "cag", "gaa", "ctc", "ctc", "cgt", "acc", "ctc", "aac", "cag", "cca", "gac", "agc", "cag", "ctc", "cag", "ctg", "acc", "acc", "ggc", "aat", "ggc", "ctg", "ttc", "ctc", "agc", "gag", "ggc", "ctg", "aag", "cta", "gtg", "gat", "aag", "ttt", "ttg", "gag", "gat", "gtt", "aaa", "aag", "ttg", "tac", "cac", "tca", "gaa", "gcc", "ttc", "act", "gtc", "aac", "ttc", "ggg", "gac", "acc", "gaa", "gag", "gcc", "aag", "aaa", "cag", "atc", "aac", "gat", "tac", "gtg", "gag", "aag", "ggt", "act", "caa", "ggg", "aaa", "att", "gtg", "gat", "ttg", "gtc", "aag", "gag", "ctt", "gac", "aga", "gac", "aca", "gtt", "ttt", "gct", "ctg", "gtg", "aat", "tac", "atc", "ttc", "ttt", "aaa", "ggc", "aaa", "tgg", "gag", "aga", "ccc", "ttt", "gaa", "gtc", "aag", "gac", "acc", "gag", "gaa", "gag", "gac", "ttc", "cac", "gtg", "gac", "cag", "gtg", "acc", "acc", "gtg", "aag", "gtg", "cct", "atg", "atg", "aag", "cgt", "tta", "ggc", "atg", "ttt", "aac", "atc", "cag", "cac", "tgt", "aag", "aag", "ctg", "tcc", "agc", "tgg", "gtg", "ctg", "ctg", "atg", "aaa", "tac", "ctg", "ggc", "aat", "gcc", "acc", "gcc", "atc", "ttc", "ttc", "ctg", "cct", "gat", "gag", "ggg", "aaa", "cta", "cag", "cac", "ctg", "gaa", "aat", "gaa", "ctc", "acc", "cac", "gat", "atc", "atc", "acc", "aag", "ttc", "ctg", "gaa", "aat", "gaa", "gac", "aga", "agg", "tct", "gcc", "agc", "tta", "cat", "tta", "ccc", "aaa", "ctg", "tcc", "att", "act", "gga", "acc", "tat", "gat", "ctg", "aag", "agc", "gtc", "ctg", "ggt", "caa", "ctg", "ggc", "atc", "act", "aag", "gtc", "ttc", "agc", "aat", "ggg", "gct", "gac", "ctc", "tcc", "ggg", "gtc", "aca", "gag", "gag", "gca", "ccc", "ctg", "aag", "ctc", "tcc", "aag", "gcc", "gtg", "cat", "aag", "gct", "gtg", "ctg", "acc", "atc", "gac", "gag", "aaa", "ggg", "act", "gaa", "gct", "gct", "ggg", "gcc", "atg", "ttt", "tta", "gag", "gcc", "ata", "ccc", "atg", "tct", "atc", "ccc", "ccc", "gag", "gtc", "aag", "ttc", "aac", "aaa", "ccc", "ttt", "gtc", "ttc", "tta", "atg", "att", "gaa", "caa", "aat", "acc", "aag", "tct", "ccc", "ctc", "ttc", "atg", "gga", "aaa", "gtg", "gtg", "aat", "ccc", "acc", "caa", "aaa"};
	
	string currentGene = " ";
	string ID = "";
  vector<string> words = HadoopUtils::splitString( line, " " );
    
  string pat;
		
	if(words.size() > 0)
  {
		unsigned i;
		for(i=0; i < words[0].length();i++)
		{
			if(words[0].at(i) == '_') break;
			else if(words[0].at(i) != '>') tmp = tmp + words[0].at(i);
			
		}
		
    pat = tmp;
		tmp = "";
		
		i = words[0].find_first_of("_") + 1;
		for(; i < words[0].length();i++)
		{
			tmp = tmp + words[0].at(i);
			
		}
		ID = tmp;
		
	}
	
	string refSeq = " ";
	string patSeq = " ";
	int cont=0;
	int i=0;
	if(pat.compare(currentGene) != 0)
	{
		// ABCB4
		if(pat.compare("ABCB4") == 0)
		{
			currentGene = "ABCB4";
			
			while(i < words.size())
			{
				patSeq = words[cont];			
				refSeq = ABCB4[cont];
				
				std::stringstream out;
				out << cont;
							
				if ('n'!=patSeq[0] && 'n'!=patSeq[1] && 'n'!= patSeq[2])
				{
					if (patSeq[0] != refSeq[0])
					{
						if (patSeq[2] != refSeq[2])
						{
							tmp = "";
							
							tmp = ID + "_" + out.str() + "_3_" + refSeq + "_" + patSeq; 
							
							context.emit(pat, tmp);
						}
						tmp = "";
						tmp = ID + "_" + out.str() + "_1_" + refSeq + "_" + patSeq;
						context.emit(pat, tmp);
					}
				}
				else if (patSeq[1] != refSeq[1])
				{
					tmp = "";
					tmp = ID + "_" + out.str() + "_2_" + refSeq + "_" + patSeq;
					context.emit(pat, tmp);
				}
				else if (patSeq[2] != refSeq[2])
				{
					tmp = "";
					tmp = ID + "_" + out.str() + "_3_" + refSeq + "_" + patSeq;
					context.emit(pat, tmp);
				}
				cont++;
				i++;
			}
		}
		// ATP8B1
		else if(pat.compare("ATP8B1") == 0)
		{
			currentGene = "ATP8B1";
			
			while (i < words.size())
			{
				patSeq = words[cont];			
				refSeq = ABCB4[cont];
				
				std::stringstream out;
				out << cont;
							
				if ('n'!=patSeq[0] && 'n'!=patSeq[1] && 'n'!= patSeq[2])
				{
					if (patSeq[0] != refSeq[0])
					{
						if (patSeq[2] != refSeq[2])
						{
							tmp = "";
							
							
							
							tmp = ID + "_" + out.str() + "_3_" + refSeq + "_" + patSeq; 
							
							context.emit(pat, tmp);
						}
						tmp = "";
						tmp = ID + "_" + out.str() + "_1_" + refSeq + "_" + patSeq;
						context.emit(pat, tmp);
					}
				}
				else if (patSeq[1] != refSeq[1])
				{
					tmp = "";
					tmp = ID + "_" + out.str() + "_2_" + refSeq + "_" + patSeq;
					context.emit(pat, tmp);
				}
				else if (patSeq[2] != refSeq[2])
				{
					tmp = "";
					tmp = ID + "_" + out.str() + "_3_" + refSeq + "_" + patSeq;
					context.emit(pat, tmp);
				}
				cont++;
				i++;
			}
		}
		// JAG1
		else if(pat.compare("JAG1") == 0)
		{
			currentGene = "JAG1";
			
			while (i < words.size())
			{
				patSeq = words[cont];			
				refSeq = ABCB4[cont];
				
				std::stringstream out;
				out << cont;
							
				if ('n'!=patSeq[0] && 'n'!=patSeq[1] && 'n'!= patSeq[2])
				{
					if (patSeq[0] != refSeq[0])
					{
						if (patSeq[2] != refSeq[2])
						{
							tmp = "";
							
							
							
							tmp = ID + "_" + out.str() + "_3_" + refSeq + "_" + patSeq; 
							
							context.emit(pat, tmp);
						}
						tmp = "";
						tmp = ID + "_" + out.str() + "_1_" + refSeq + "_" + patSeq;
						context.emit(pat, tmp);
					}
				}
				else if (patSeq[1] != refSeq[1])
				{
					tmp = "";
					tmp = ID + "_" + out.str() + "_2_" + refSeq + "_" + patSeq;
					context.emit(pat, tmp);
				}
				else if (patSeq[2] != refSeq[2])
				{
					tmp = "";
					tmp = ID + "_" + out.str() + "_3_" + refSeq + "_" + patSeq;
					context.emit(pat, tmp);
				}
				cont++;
				i++;
			}
		}
		// SERPINA1
		else if(pat.compare("SERPINA1") == 0)
		{
			currentGene = "SERPINA1";
			
			while (i < words.size())
			{
				patSeq = words[cont];			
				refSeq = ABCB4[cont];
				
				std::stringstream out;
				out << cont;
							
				if ('n'!=patSeq[0] && 'n'!=patSeq[1] && 'n'!= patSeq[2])
				{
					if (patSeq[0] != refSeq[0])
					{
						if (patSeq[2] != refSeq[2])
						{
							tmp = "";
							
							
							
							tmp = ID + "_" + out.str() + "_3_" + refSeq + "_" + patSeq; 
							
							context.emit(pat, tmp);
						}
						tmp = "";
						tmp = ID + "_" + out.str() + "_1_" + refSeq + "_" + patSeq;
						context.emit(pat, tmp);
					}
				}
				else if (patSeq[1] != refSeq[1])
				{
					tmp = "";
					tmp = ID + "_" + out.str() + "_2_" + refSeq + "_" + patSeq;
					context.emit(pat, tmp);
				}
				else if (patSeq[2] != refSeq[2])
				{
					tmp = "";
					tmp = ID + "_" + out.str() + "_3_" + refSeq + "_" + patSeq;
					context.emit(pat, tmp);
				}
				cont++;
				i++;
			}
		}
		//ABCB11
		else if(pat.compare("ABCB11") == 0)
		{
			currentGene = "ABCB11";
			
			while (i < words.size())
			{
				patSeq = words[cont];			
				refSeq = ABCB4[cont];
				
				std::stringstream out;
				out << cont;
							
				if ('n'!=patSeq[0] && 'n'!=patSeq[1] && 'n'!= patSeq[2])
				{
					if (patSeq[0] != refSeq[0])
					{
						if (patSeq[2] != refSeq[2])
						{
							tmp = "";
							
							
							
							tmp = ID + "_" + out.str() + "_3_" + refSeq + "_" + patSeq; 
							
							context.emit(pat, tmp);
						}
						tmp = "";
						tmp = ID + "_" + out.str() + "_1_" + refSeq + "_" + patSeq;
						context.emit(pat, tmp);
					}
				}
				else if (patSeq[1] != refSeq[1])
				{
					tmp = "";
					tmp = ID + "_" + out.str() + "_2_" + refSeq + "_" + patSeq;
					context.emit(pat, tmp);
				}
				else if (patSeq[2] != refSeq[2])
				{
					tmp = "";
					tmp = ID + "_" + out.str() + "_3_" + refSeq + "_" + patSeq;
					context.emit(pat, tmp);
				}
				cont++;
				i++;
			}
		}
	 }
  }
};
 
class DiseaseApplicationReducer : public HadoopPipes::Reducer
{

  public: DiseaseApplicationReducer(HadoopPipes::TaskContext& context)
  {

  }

  void reduce( HadoopPipes::ReduceContext& context ) 
  {
    
    string ABCB4[] = {"590","175","320","144","957","546","1168","403","1016"};
	  string ABCB11[] = {"432","1057","575","297","90"};
	  string ATP8B1[] = {"70","288","308","456","554","602","661","867","892","952"};
	  string JAG1[] = {"274","184","184","37","234"};
	  string SERPINA1[] = {"400","237","288","125","360","139","77","366","247","341","91","65","116","63","387","377","382","280","365","228","393","184","241","26","109","184"};

	  while (context.nextValue())
	  {
		 string line = context.getInputValue();
		 string line2 = context.getInputKey();
		 
		 string tmp = "";
		 string ID,number1,number2,def,mod;
		 
		 unsigned i,j;
		 for(i=0; i < line.length();i++)
		 {
			if(line.at(i) == '_') break;
			tmp = tmp + line.at(i);	
		 }
		 i++;
		 ID = tmp;
		 tmp = "";
		 for(; i < line.length();i++)
		 {
			if(line.at(i) == '_') break;
			tmp = tmp + line.at(i);
		 }
		 number1 = tmp;
		 tmp = "";
		 i++;
		 for(; i < line.length();i++)
		 {
			if(line.at(i) == '_') break;
			tmp = tmp + line.at(i);
		 }
		 i++;
		 number2 = tmp;
		 tmp = "";
		 for(; i < line.length();i++)
		 {
			if(line.at(i) == '_') break;
			tmp = tmp + line.at(i);
		 }
		 i++;
		 def = tmp;
		 tmp = "";
		 for(; i < line.length();i++)
		 {
			if(line.at(i) == '_') break;
			tmp = tmp + line.at(i);
		 }
		 mod = tmp;
		 i = 0;
	     string number;
	     if(line2 == "ABCB4")
         {
				while (i < 9)
				{
					  if(number1 == ABCB4[i])
					  {
						  string tmp2 = line + " - DB data: " + number1 + number2;
						  context.emit(line2,tmp2);
					  }
					  i++;  	  
				}
			}
		else if(line2 == "ABCB11")
    {
				while (i < 5)
				{
					  if(number1 == ABCB4[i])
					  {
						  string tmp2 = line + " - DB data: " + number1 + number2;
						  context.emit(line2,tmp2);
					  }
					  i++;  	  
				}
			}
		else if(line2 == "ATP8B1")
    {
				while (i < 10)
				{
					  if(number1 == ABCB4[i])
					  {
						  string tmp2 = line + " - DB data: " + number1 + number2;
						  context.emit(line2,tmp2);
					  }
					  i++;  	  
				}
		}
		else if(line2 == "JAG1")
    {
				while (i < 5)
				{
					  if(number1 == ABCB4[i])
					  {
						  string tmp2 = line + " - DB data: " + number1 + number2;
						  context.emit(line2,tmp2);
					  }
					  i++;  	  
				}
		}
		else if(line2 == "SERPINA1")
    {
				while (i < 22)
				{
					  if(number1 == ABCB4[i])
					  {
						  string tmp2 = line + " - DB data: " + number1 + number2;
						  context.emit(line2,tmp2);
					  }
					  i++;  	  
				}
		}
	}
}

};
 
int main(int argc, char *argv[])
{
  return HadoopPipes::runTask(HadoopPipes::TemplateFactory<DiseaseApplicationMapper,DiseaseApplicationReducer >() );
}


