//-------------------------------------------//
//                                           //
//   	TABLEDV. CPP                           //
//                                           //
//    Copyright (C) 1994 by Eduardo Bezerra  //
//                                           //
//-------------------------------------------//


#include <classlib\date.h>
#include <dir.h>

#include "globals.h"
#include "tabledv.h"


/////////////////////////////////////
//    GARG BOR1
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqBOR1Fields [] =
{
	{ "CODIGO"     , 'C' , 1 , 0 },    /* 1 */
	{ "BOLSA"      , 'C' , 4 , 0 },    /* 2 */
	{ "DATA"       , 'D' , 8 , 0 },    /* 3 */
	{ "REGISTROS"  , 'N' , 4 , 0 },    /* 4 */
	{ "BOLETIM"    , 'C' , 1 , 0 },    /* 5 */
	{ 0,0,0,0 }
};

static TAG4INFO GarqBOR1Tags [] =
{
	{ "TAG_1", "DATA", 0,0,0 },
	{ 0,0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG BOR2
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqBOR2Fields [] =
{
	{ "CODIGO"     , 'C' , 1 , 0 },    /* 1 */
	{ "SETOR"      , 'C' , 4 , 0 },    /* 2 */
	{ "VOLUME"     , 'N' , 9 , 0 },    /* 3 */
	{ "QUANTIDADE" , 'N' , 9 , 0 },    /* 4 */
	{ "IBV_MEDIO"  , 'N' , 7 , 0 },    /* 5 */
	{ "OSCILACAO"  , 'N' , 6 , 2 },    /* 6 */
	{ "SINAL"      , 'C' , 1 , 0 },    /* 7 */
	{ "MAXIMA"     , 'N' , 7 , 0 },    /* 8 */
	{ "MINIMA"     , 'N' , 7 , 0 },    /* 9 */
	{ "IBV_FECH"   , 'N' , 7 , 0 },    /* 10 */
	{ "_OSCILACAO" , 'N' , 5 , 0 },    /* 11 */
	{ "_SINAL"     , 'C' , 1 , 0 },    /* 12 */
	{ "MAXIMA_DIA" , 'N' , 7 , 0 },    /* 13 */
	{ "MINIMA_DIA" , 'N' , 7 , 0 },    /* 14 */
	{ 0,0,0,0 }
};

static TAG4INFO GarqBOR2Tags [] =
{
	{ "TAG_1", "SETOR", 0,0,0 },
	{ 0,0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG BOR3
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqBOR3Fields [] =
{
	{ "CODIGO"     , 'C' , 1 , 0 },    /* 1 */
	{ "PRACA"      , 'C' , 3 , 0 },    /* 2 */
	{ "NOME"       , 'C' , 30, 0 },    /* 3 */
	{ "NEGOCIADO"  , 'N' , 11, 0 },    /* 4 */
	{ "REALIZADO"  , 'N' , 5 , 0 },    /* 5 */
	{ "VOLUME"     , 'N' , 18, 2 },    /* 6 */
	{ 0,0,0,0 }
};

static TAG4INFO GarqBOR3Tags [] =
{
	{ "TAG_1", "PRACA+NOME", 0,0,0 },
	{ 0,0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG BOR4
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqBOR4Fields [] =
{
	{ "CODIGO"     , 'C' , 1 , 0 },    /* 1 */
	{ "FECHAMENTO" , 'N' , 7 , 0 },    /* 2 */
	{ "MAXIMO"     , 'N' , 7 , 0 },    /* 3 */
	{ "MINIMO"     , 'N' , 7 , 0 },    /* 4 */
	{ "MEDIO"      , 'N' , 7 , 0 },    /* 5 */
	{ "ULTIMO"     , 'N' , 7 , 0 },    /* 6 */
	{ "SINAL"      , 'C' , 1 , 0 },    /* 7 */
	{ "OSCILACAO"  , 'N' , 6 , 2 },    /* 8 */
	{ "INDICE_MES" , 'N' , 7 , 0 },    /* 9 */
	{ "INDICE_ANO" , 'N' , 7 , 0 },    /* 10 */
	{ 0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG BOR5
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqBOR5Fields [] =
{
	{ "MERCADO"    , 'C' , 1 , 0 },    /* 1 */
	{ "CODCIA"     , 'C' , 4 , 0 },    /* 2 */
	{ "NOMECIA"    , 'C' , 20, 0 },    /* 3 */
	{ "TIPO"       , 'C' , 2 , 0 },    /* 4 */
	{ "DIREITOS"   , 'C' , 3 , 0 },    /* 5 */
	{ "VENCIMENTO" , 'C' , 3 , 0 },    /* 6 */
	{ "OPCOES"     , 'N' , 8 , 2 },    /* 7 */
	{ "NEGOCIADOS" , 'N' , 13, 0 },    /* 8 */
	{ "ABERTURA"   , 'N' , 8 , 2 },    /* 9 */
	{ "FECHAMENTO" , 'N' , 8 , 2 },    /* 10 */
	{ "MAXIMA"     , 'N' , 8 , 2 },    /* 11 */
	{ "MINIMA"     , 'N' , 8 , 2 },    /* 12 */
	{ "MEDIA"      , 'N' , 8 , 2 },    /* 13 */
	{ "OSCILACAO"  , 'N' , 6 , 2 },    /* 14 */
	{ "SINAL"      , 'C' , 1 , 0 },    /* 15 */
	{ "VOLUME"     , 'N' , 15, 2 },    /* 16 */
	{ "PERCENTUAL" , 'N' , 7 , 3 },    /* 17 */
	{ "INDICE"     , 'N' , 8 , 2 },    /* 18 */
	{ "REALIZADOS" , 'N' , 4 , 0 },    /* 19 */
	{ "COMPRA"     , 'N' , 8 , 2 },    /* 20 */
	{ "VENDA"      , 'N' , 8 , 2 },    /* 21 */
	{ "UNIDADE"    , 'C' , 1 , 0 },    /* 22 */
	{ "SITUACAO"   , 'C' , 1 , 0 },    /* 23 */
	{ 0,0,0,0 }
};

static TAG4INFO GarqBORTags [] =
{
	{ "TAG_1", "CODCIA+TIPO", 0,0,0 },
	{ 0,0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG BRx
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqBRxFields [] =
{
	{ "MERCADO"    , 'C' , 1 , 0 },    /* 1 */
	{ "CODCIA"     , 'C' , 4 , 0 },    /* 2 */
	{ "NOMECIA"    , 'C' , 20, 0 },    /* 3 */
	{ "TIPO"       , 'C' , 2 , 0 },    /* 4 */
	{ "DIREITOS"   , 'C' , 3 , 0 },    /* 5 */
	{ "VENCIMENTO" , 'C' , 3 , 0 },    /* 6 */
	{ "OPCOES"     , 'N' , 8 , 2 },    /* 7 */
	{ "NEGOCIADOS" , 'N' , 13, 0 },    /* 8 */
	{ "ABERTURA"   , 'N' , 8 , 2 },    /* 9 */
	{ "FECHAMENTO" , 'N' , 8 , 2 },    /* 10 */
	{ "MAXIMA"     , 'N' , 8 , 2 },    /* 11 */
	{ "MINIMA"     , 'N' , 8 , 2 },    /* 12 */
	{ "MEDIA"      , 'N' , 8 , 2 },    /* 13 */
	{ "OSCILACAO"  , 'N' , 6 , 2 },    /* 14 */
	{ "SINAL"      , 'C' , 1 , 0 },    /* 15 */
	{ "VOLUME"     , 'N' , 15, 2 },    /* 16 */
	{ "PERCENTUAL" , 'N' , 7 , 3 },    /* 17 */
	{ "INDICE"     , 'N' , 8 , 2 },    /* 18 */
	{ "REALIZADOS" , 'N' , 4 , 0 },    /* 19 */
	{ 0,0,0,0 }
};

static TAG4INFO GarqBRxTags [] =
{
	{ "TAG_1", "CODCIA+TIPO", 0,0,0 },
	{ 0,0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG BRI
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqBRIFields [] =
{
	{ "CODIGO"     , 'C' , 1 , 0 },    /* 1 */
	{ "SETOR"      , 'C' , 4 , 0 },    /* 2 */
	{ "VOLUME"     , 'N' , 9 , 0 },    /* 3 */
	{ "QUANTIDADE" , 'N' , 9 , 0 },    /* 4 */
	{ "IBV_MEDIO"  , 'N' , 7 , 0 },    /* 5 */
	{ "OSCILACAO"  , 'N' , 6 , 2 },    /* 6 */
	{ "SINAL"      , 'C' , 1 , 0 },    /* 7 */
	{ "MAXIMA"     , 'N' , 7 , 0 },    /* 8 */
	{ "MINIMA"     , 'N' , 7 , 0 },    /* 9 */
	{ "IBV_FECH"   , 'N' , 7 , 0 },    /* 10 */
	{ "_OSCILACAO" , 'N' , 5 , 0 },    /* 11 */
	{ "_SINAL"     , 'C' , 1 , 0 },    /* 12 */
	{ "MAXIMA_DIA" , 'N' , 7 , 0 },    /* 13 */
	{ "MINIMA_DIA" , 'N' , 7 , 0 },    /* 14 */
	{ 0,0,0,0 }
};

static TAG4INFO GarqBRITags [] =
{
	{ "TAG_1", "SETOR", 0,0,0 },
	{ 0,0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG BFR1
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqBFR1Fields [] =
{
	{ "CODIGO"     , 'C' , 1 , 0 },    /* 1 */
	{ "BOLSA"      , 'C' , 4 , 0 },    /* 2 */
	{ "DATA"       , 'D' , 8 , 0 },    /* 3 */
	{ "REGISTROS"  , 'N' , 4 , 0 },    /* 4 */
	{ 0,0,0,0 }
};

static TAG4INFO GarqBFR1Tags [] =
{
	{ "TAG_1", "DATA", 0,0,0 },
	{ 0,0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG BFR2
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqBFR2Fields [] =
{
	{ "CODIGO"     , 'C' , 1 , 0 },    /* 1 */
	{ "SETOR"      , 'C' , 1 , 0 },    /* 2 */
	{ "VOLUME"     , 'N' , 9 , 0 },    /* 3 */
	{ "QUANTIDADE" , 'N' , 9 , 0 },    /* 4 */
	{ "FECHAMENTO" , 'N' , 8 , 2 },    /* 5 */
	{ "OSCILACAO"  , 'N' , 6 , 2 },    /* 6 */
	{ "SINAL"      , 'C' , 1 , 0 },    /* 7 */
	{ "MAXIMA"     , 'N' , 8 , 2 },    /* 8 */
	{ "MINIMA"     , 'N' , 8 , 2 },    /* 9 */
	{ "IBV_FECH"   , 'N' , 8 , 2 },    /* 10 */
	{ "_OSCILACAO" , 'N' , 6 , 2 },    /* 11 */
	{ "_SINAL"     , 'C' , 1 , 0 },    /* 12 */
	{ "MAXIMA_DIA" , 'N' , 8 , 2 },    /* 13 */
	{ "MINIMA_DIA" , 'N' , 8 , 2 },    /* 14 */
	{ 0,0,0,0 }
};

static TAG4INFO GarqBFR2Tags [] =
{
	{ "TAG_1", "SETOR", 0,0,0 },
	{ 0,0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG BFR3
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqBFR3Fields [] =
{
	{ "MERCADO"    , 'C' , 1 , 0 },    /* 1 */
	{ "CODCIA"     , 'C' , 4 , 0 },    /* 2 */
	{ "NOMECIA"    , 'C' , 20, 0 },    /* 3 */
	{ "TIPO"       , 'C' , 2 , 0 },    /* 4 */
	{ "DIREITOS"   , 'C' , 3 , 0 },    /* 5 */
	{ "VENCIMENTO" , 'C' , 3 , 0 },    /* 6 */
	{ "OPCOES"     , 'N' , 8 , 2 },    /* 7 */
	{ "NEGOCIADOS" , 'N' , 13, 0 },    /* 8 */
	{ "ABERTURA"   , 'N' , 8 , 2 },    /* 9 */
	{ "FECHAMENTO" , 'N' , 8 , 2 },    /* 10 */
	{ "MAXIMA"     , 'N' , 8 , 2 },    /* 11 */
	{ "MINIMA"     , 'N' , 8 , 2 },    /* 12 */
	{ "MEDIA"      , 'N' , 8 , 2 },    /* 13 */
	{ "OSCILACAO"  , 'N' , 6 , 2 },    /* 14 */
	{ "SINAL"      , 'C' , 1 , 0 },    /* 15 */
	{ "VOLUME"     , 'N' , 15, 2 },    /* 16 */
	{ "PERCENTUAL" , 'N' , 7 , 3 },    /* 17 */
	{ "INDICE"     , 'N' , 8 , 2 },    /* 18 */
	{ "REALIZADOS" , 'N' , 4 , 0 },    /* 19 */
	{ 0,0,0,0 }
};

static TAG4INFO GarqBFR3Tags [] =
{
	{ "TAG_1", "CODCIA+TIPO", 0,0,0 },
	{ 0,0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG BSx
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqBSxFields [] =
{
	{ "NOMECIA"    , 'C', 12, 0 },    /* 1 */
	{ "PAPEL"      , 'C', 10, 0 },    /* 2 */
	{ "INDICADOR"  , 'C', 1 , 0 },    /* 3 */
	{ "CODCIA"     , 'C', 4 , 0 },    /* 4 */
	{ "NUMCIA"     , 'C', 2 , 0 },    /* 5 */
	{ "MERCADO"    , 'C', 3 , 0 },    /* 6 */
	{ "PRAZO"      , 'C', 2 , 0 },    /* 7 */
	{ "CONTRATO"   , 'C', 2 , 0 },    /* 8 */
	{ "CODIGO"     , 'C', 4 , 0 },    /* 9 */
	{ "TIPO"       , 'C', 2 , 0 },    /* 10 */
	{ "ESPECIE"    , 'C', 4 , 0 },    /* 11 */
	{ "NUMERO"     , 'C', 3 , 0 },    /* 12 */
	{ "PRIMEIRO"   , 'N', 10, 2 },    /* 13 */
	{ "MAIOR"      , 'N', 10, 2 },    /* 14 */
	{ "MENOR"      , 'N', 10, 2 },    /* 15 */
	{ "MEDIO"      , 'N', 10, 2 },    /* 16 */
	{ "ULTIMO"     , 'N', 10, 2 },    /* 17 */
	{ "TENDENCIA"  , 'C', 1 , 0 },    /* 18 */
	{ "OSCILACAO"  , 'N', 6 , 2 },    /* 19 */
	{ "COMPRA"     , 'N', 10, 2 },    /* 20 */
	{ "VENDA"      , 'N', 10, 2 },    /* 21 */
	{ "NEGOCIOS"   , 'N', 4 , 0 },    /* 22 */
	{ "NEGOCIADOS" , 'N', 11, 0 },    /* 23 */
	{ 0,0,0,0 }
};

static TAG4INFO GarqBSxTags [] =
{
	{ "TAG_1", "NOMECIA", 0,0,0 },
	{ 0,0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG BSI
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqBSIFields [] =
{
	{ "DATA"       , 'D', 8 , 0 },    /* 1 */
	{ "ABERTURA"   , 'N', 6 , 0 },    /* 2 */
	{ "MINIMO"     , 'N', 6 , 0 },    /* 3 */
	{ "MAXIMO"     , 'N', 6 , 0 },    /* 4 */
	{ "MEDIO"      , 'N', 6 , 0 },    /* 5 */
	{ "FECHAMENTO" , 'N', 6 , 0 },    /* 6 */
	{ "TENDENCIA"  , 'C', 1 , 0 },    /* 7 */
	{ "EVOLUCAO"   , 'N', 5 , 1 },    /* 8 */
	{ "NEGOCIOS"   , 'N', 5 , 0 },    /* 9 */
	{ "NEGOCIADOS" , 'N', 13, 0 },    /* 10 */
	{ "VOLUME"     , 'N', 14, 2 },    /* 11 */
	{ 0,0,0,0 }
};

static TAG4INFO GarqBSITags [] =
{
	{ "TAG_1", "DATA", 0,0,0 },
	{ 0,0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG BAS1
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqBAS1Fields [] =
{
	{ "DATA"       , 'D', 8 , 0 },    /* 1 */
	{ "ABERTURA"   , 'N', 6 , 0 },    /* 2 */
	{ "MINIMO"     , 'N', 6 , 0 },    /* 3 */
	{ "MAXIMO"     , 'N', 6 , 0 },    /* 4 */
	{ "MEDIO"      , 'N', 6 , 0 },    /* 5 */
	{ "FECHAMENTO" , 'N', 6 , 0 },    /* 6 */
	{ "TENDENCIA"  , 'C', 1 , 0 },    /* 7 */
	{ "EVOLUCAO"   , 'N', 5 , 1 },    /* 8 */
	{ "NEGOCIOS"   , 'N', 5 , 0 },    /* 9 */
	{ "NEGOCIADOS" , 'N', 13, 0 },    /* 10 */
	{ "VOLUME"     , 'N', 14, 2 },    /* 11 */
	{ 0,0,0,0 }
};

static TAG4INFO GarqBAS1Tags [] =
{
	{ "TAG_1", "DATA", 0,0,0 },
	{ 0,0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG BAS2
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqBAS2Fields [] =
{
	{ "NOMECIA"    , 'C', 12, 0 },    /* 1 */
	{ "PAPEL"      , 'C', 10, 0 },    /* 2 */
	{ "INDICADOR"  , 'C', 1 , 0 },    /* 3 */
	{ "CODCIA"     , 'C', 4 , 0 },    /* 4 */
	{ "NUMCIA"     , 'C', 2 , 0 },    /* 5 */
	{ "MERCADO"    , 'C', 3 , 0 },    /* 6 */
	{ "PRAZO"      , 'C', 2 , 0 },    /* 7 */
	{ "CONTRATO"   , 'C', 2 , 0 },    /* 8 */
	{ "CODIGO"     , 'C', 4 , 0 },    /* 9 */
	{ "TIPO"       , 'C', 2 , 0 },    /* 10 */
	{ "ESPECIE"    , 'C', 4 , 0 },    /* 11 */
	{ "NUMERO"     , 'C', 3 , 0 },    /* 12 */
	{ "PRIMEIRO"   , 'N', 10, 2 },    /* 13 */
	{ "MAIOR"      , 'N', 10, 2 },    /* 14 */
	{ "MENOR"      , 'N', 10, 2 },    /* 15 */
	{ "MEDIO"      , 'N', 10, 2 },    /* 16 */
	{ "ULTIMO"     , 'N', 10, 2 },    /* 17 */
	{ "TENDENCIA"  , 'C', 1 , 0 },    /* 18 */
	{ "OSCILACAO"  , 'N', 6 , 2 },    /* 19 */
	{ "COMPRA"     , 'N', 10, 2 },    /* 20 */
	{ "VENDA"      , 'N', 10, 2 },    /* 21 */
	{ "NEGOCIOS"   , 'N', 4 , 0 },    /* 22 */
	{ "NEGOCIADOS" , 'N', 11, 0 },    /* 23 */
	{ 0,0,0,0 }
};

static TAG4INFO GarqBAS2Tags [] =
{
	{ "TAG_1", "NOMECIA", 0,0,0 },
	{ 0,0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG BRJDATA
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqBRJDATAFields [] =
{
	{ "PROTOCOLO"  , 'C' , 10 , 0 },  /* 1 */
	{ "FECHAMENTO" , 'C' , 1  , 0 },  /* 2 */
	{ "DATA_1"     , 'D' , 8  , 0 },  /* 3 */
	{ "DATA_2"     , 'D' , 8  , 0 },  /* 4 */
	{ "DATA_3"     , 'D' , 8  , 0 },  /* 5 */
	{ "DATA_4"     , 'D' , 8  , 0 },  /* 6 */
	{ "DATA_5"     , 'D' , 8  , 0 },  /* 7 */
	{ 0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG BSPDATA
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqBSPDATAFields [] =
{
	{ "PROTOCOLO"  , 'C' , 10 , 0 },  /* 1 */
	{ "DATA"       , 'D' , 8  , 0 },  /* 2 */
	{ 0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG BIG
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqBIGFields [] =
{
	{ "DATA"      , 'D' , 8 , 0 },
	{ "HORA"      , 'C' , 8 , 0 },
	{ "CODCIA"    , 'C' , 4 , 0 },
	{ "TIPO"      , 'C' , 2 , 0 },
	{ "DIREITOS"  , 'C' , 3 , 0 },
	{ "VENCIMENTO", 'C' , 3 , 0 },
	{ "ULTIMA"    , 'N' , 8 , 2 },
	{ "MEDIA"     , 'N' , 8 , 2 },
	{ "FECHAMENTO", 'N' , 8 , 2 },
	{ 0,0,0,0 }
};

static TAG4INFO GarqBIGTags [] =
{
	{ "TAG_1", "CODCIA+TIPO+DTOS(DATA)+HORA", 0,0,0 },
	{ 0,0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG NEG
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqNEGFields [] =
{
	{ "CODCIA"     , 'C' , 4 , 0 },    /* 1 */
	{ "TIPO"       , 'C' , 2 , 0 },    /* 2 */
	{ "DIREITOS"   , 'C' , 3 , 0 },    /* 3 */
	{ "VENCIMENTO" , 'C' , 3 , 0 },    /* 4 */
	{ "NEGOCIADOS" , 'N' , 7 , 0 },    /* 5 */
	{ "PRECOACOES" , 'N' , 8 , 2 },    /* 6 */
	{ "DATA_BOLSA" , 'D' , 8 , 0 },    /* 7 */
	{ "HORA"       , 'C' , 8 , 0 },    /* 8 */
	{ "No_NEGOCIO" , 'N' , 9 , 0 },    /* 9 */
	{ "CORRETORAA" , 'C' , 3 , 0 },    /* 10 */
	{ "TP_NEGOCIO" , 'C' , 1 , 0 },    /* 11 */
	{ "CORRETORAB" , 'C' , 3 , 0 },    /* 12 */
	{ 0,0,0,0 }
};

static TAG4INFO GarqNEGTags [] =
{
	{ "TAG_1", "CODCIA+TIPO", 0,0,0 },
	{ 0,0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG HIS
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqHISFields [] =
{
	{ "DATA"      , 'D' , 8 , 0 },
	{ "CODCIA"    , 'C' , 4 , 0 },
	{ "TIPO"      , 'C' , 2 , 0 },
	{ "DIREITOS"  , 'C' , 3 , 0 },
	{ "VENCIMENTO", 'C' , 3 , 0 },
	{ "OSCILACAO" , 'N' , 6 , 2 },
	{ "SINAL"     , 'C' , 1 , 0 },
	{ "MINIMA"    , 'N' , 8 , 2 },
	{ "MAXIMA"    , 'N' , 8 , 2 },
	{ "MEDIA"     , 'N' , 8 , 2 },
	{ "ABERTURA"  , 'N' , 8 , 2 },
	{ "FECHAMENTO", 'N' , 8 , 2 },
	{ "NEGOCIADOS", 'N' , 13, 0 },
	{ "REALIZADOS", 'N' , 4 , 0 },
	{ 0,0,0,0 }
};

static TAG4INFO GarqHISTags [] =
{
	{ "TAG_1", "CODCIA+TIPO+DTOS(DATA)", 0,0,0 },
	{ 0,0,0,0,0 }
};

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    GARG IND
//		       DBF and Index Structures
//    ===============================
//
static FIELD4INFO GarqINDFields [] =
{
	{ "SETOR"      , 'C' , 2 , 0 },
	{ "DATA_BOLSA" , 'D' , 8 , 0 },
	{ "IBV_MEDIO"  , 'N' , 8 , 0 },
	{ "IBV_FECH"   , 'N' , 8 , 0 },
	{ 0,0,0,0 }
};

static TAG4INFO GarqINDTags [] =
{
	{ "TAG_1", "DTOS(DATA_BOLSA)+SETOR", 0,0,0 },
	{ 0,0,0,0,0 }
};


//--------------------------------------------//
//                 Global Data                //
//--------------------------------------------//

string colon   = ':' ,
		 period  = '.' ;

extern Code4 __code4;

//--------------------------------------------//
//                  Local Data                //
//--------------------------------------------//

const uint MAX_GARQ_TYPES = 21;

static GarqNumFldsInfo[] = {

	0,       /* 0 */
	5,       /* 1 */
	14,      /* 2 */
	6,       /* 3 */
	10,      /* 4 */
	23,      /* 5 */
	19,      /* 6 */
	0,       /* 7 */
	4,       /* 8 */
	14,      /* 9 */
	19,      /* 10 */
	23,      /* 11 */
	11,      /* 12 */
	11,      /* 13 */
	23,      /* 14 */
	6,       /* 15 */
	2,       /* 16 */
	9,       /* 17 */
	12,      /* 18 */
	14,      /* 19 */
	4        /* 20 */
};

static FIELD4INFO* GarqField4Info [] = {

	0,                                /* 0 */
	GarqBOR1Fields,                   /* 1 */
	GarqBOR2Fields,                   /* 2 */
	GarqBOR3Fields,                   /* 3 */
	GarqBOR4Fields,                   /* 4 */
	GarqBOR5Fields,                   /* 5 */
	GarqBRxFields,                    /* 6 */
	GarqBRIFields,                    /* 7 */
	GarqBFR1Fields,                   /* 8 */
	GarqBFR2Fields,                   /* 9 */
	GarqBFR3Fields,                   /* 10 */
	GarqBSxFields,                    /* 11 */
	GarqBSIFields,                    /* 12 */
	GarqBAS1Fields,                   /* 13 */
	GarqBAS2Fields,                   /* 14 */
	GarqBRJDATAFields,                /* 15 */
	GarqBSPDATAFields,                /* 16 */
	GarqBIGFields,                    /* 17 */
	GarqNEGFields,                    /* 18 */
	GarqHISFields,                    /* 19 */
	GarqINDFields                     /* 20 */
};

//----------------------------------------------------------------------------//

static LPCSTR DBS     = "Documento Padrão FoxPro / dBASE";
static LPCSTR BOR1    = "Boletim de Fechamento Rio - Mestre";
static LPCSTR BOR2    = "Boletim de Fechamento Rio - Índice de Fechamento do Pregão";
static LPCSTR BOR3    = "Boletim de Fechamento Rio - SENN Totais por Praça";
static LPCSTR BOR4    = "Boletim de Fechamento Rio - Índices do SENN";
static LPCSTR BOR5    = "Boletim de Fechamento Rio - Cotações";
static LPCSTR BR      = "Boletim de Fechamento Rio - Mercados / Títulos";
static LPCSTR BRI     = "Boletim de Fechamento Rio - Índices da Bolsa Rio";
static LPCSTR BFR1    = "Bol. de Fech. Bolsa Rio 4 Últimos Pregões - Mestre";
static LPCSTR BFR2    = "Bol. de Fech. Bolsa Rio 4 Últimos Pregões - Índices";
static LPCSTR BFR3    = "Bol. de Fech. Bolsa Rio 4 Últimos Pregões - Cotações";
static LPCSTR BS      = "Boletim de Fechamento BOVESPA - Mercados / Títulos";
static LPCSTR BSI     = "Boletim de Fechamento BOVESPA - Índices";
static LPCSTR BAS1    = "Bol. de Fech. BOVESPA 4 Últimos Pregões - Mestre";
static LPCSTR BAS2    = "Bol. de Fech. BOVESPA 4 Últimos Pregões - Cotações";
static LPCSTR BRJDATA = "Datas do Boletin de Fechamento - Bolsa Rio";
static LPCSTR BSPDATA = "Datas do Boletin de Fechamento - Bolsa São Paulo";
static LPCSTR BIG     = "Boletim Instântaneo";
static LPCSTR NEG     = "Relação de Negócios";
static LPCSTR HIS     = "Séries Históricas de Ações";
static LPCSTR IND     = "Séries Históricas de Índices";

//----------------------------------------------------------------------------//

static LPCSTR GarqLabel[] = {

	DBS ,    /* 0  - Documento Padrão FoxPro / dBASE                                               */
	BOR1,    /* 1  - Bol. de Fech. Bolsa Rio - Todo Boletim / Mestre                               */
	BOR2,    /* 2  - Bol. de Fech. Bolsa Rio - Todo Boletim / Índice de Fechamento do Pregão       */
	BOR3,    /* 3  - Bol. de Fech. Bolsa Rio - Todo Boletim / SENN - Totais por Praça              */
	BOR4,    /* 4  - Bol. de Fech. Bolsa Rio - Todo Boletim / Índices do SENN                      */
	BOR5,    /* 5  - Bol. de Fech. Bolsa Rio - Todo Boletim / Cotações                             */
	BR  ,    /* 6  - Bol. de Fech. Bolsa Rio - Por Mercado, Todos os Mercados, Títulos em Ordem Alfabética, Por código de títulos */
	BRI ,    /* 7  - Bol. de Fech. Bolsa Rio - Índices da Bolsa Rio                                */
	BFR1,    /* 8  - Bol. de Fech. Bolsa Rio - 4 Últimos Pregões / Mestre                          */
	BFR2,    /* 9  - Bol. de Fech. Bolsa Rio - 4 Últimos Pregões / Índices de Fechamento do Pregão */
	BFR3,    /* 10 - Bol. de Fech. Bolsa Rio - 4 Últimos Pregões / Cotações                        */
	BS  ,    /* 11 - Bol. de Fech. BOVESPA   - Por Mercado, Por código de títulos                  */
	BSI ,    /* 12 - Bol. de Fech. BOVESPA   - Índices                                             */
	BAS1,    /* 13 - Bol. de Fech. BOVESPA   - 4 Últimos Pregões / Mestre                          */
	BAS2,    /* 14 - Bol. de Fech. BOVESPA   - 4 Últimos Pregões / Cotações                        */
	BRJDATA, /* 15 - Datas do Boletin de Fechamento - Bolsa Rio                                    */
	BSPDATA, /* 16 - Datas do Boletin de Fechamento - Bolsa São Paulo                              */
	BIG,     /* 17 - Boletim Instantâneo                                                           */
	NEG,     /* 18 - Relação de Negócios                                                           */
	HIS,     /* 19 - Séries Históricas de Ações                                                    */
	IND,     /* 20 - Séries Históricas de Índices                                                  */
};

//----------------------------------------------------------------------------//

/*-----------------------------------*
 *         Class DBFfieldInfo        *
 *-----------------------------------*/

class DBFfieldInfo
{
	public :
		DBFfieldInfo( FIELD4INFO *v ) { fields = v; }

		FIELD4INFO *fields;

		bool operator ==( DBFfieldInfo& v )
		{
			for ( int n = 0; fields[ n ].name; n++ )
			{
				if ( strcmp( fields[ n ].name, v.fields[ n ].name ) )
					return false;

				if ( fields[ n ].type != v.fields[ n ].type )
					return false;

				if ( fields[ n ].len  != v.fields[ n ].len  )
					return false;

				if ( fields[ n ].dec  != v.fields[ n ].dec  )
					return false;
			}
			return true;
		}
};

//----------------------------------------------------------------------------//

DEFINE_DOC_TEMPLATE_CLASS( TTableDocument, TTableView, TTableTemplate );

TTableTemplate tableTpl( "Arquivo FoxPro (*.DBF)", "*.dbf", 0, "DBF",
								 dtAutoDelete    | dtUpdateDir     | dtHideReadOnly |
								 dtPathMustExist | dtFileMustExist | dtOverwritePrompt );

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                         DESTRUCTOR
//    ===============================
//
TTableDocument::~TTableDocument()
{
	CloseTable();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                        CONSTRUCTOR
//    ===============================
//
TTableDocument::TTableDocument( TDocument* parent ) : TDocument( parent )
{
	TableType = NOGARQ;

	Date4 today;
	today.today();

	today.format( "CCYYMMDD" );
	date = today.ptr();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                           CanClose
//    ===============================
//
bool TTableDocument::CanClose()
{
	if ( !__is_query_running )
		return TDocument::CanClose();

	return false;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                              Close
//    ===============================
//
bool TTableDocument::Close()
{
	CloseTable();
	return true;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                               Open
//    ===============================
//
bool TTableDocument::Open( int mode, const char far* path )
{
	DocFileName = GetDocPath();

	if ( GetDocPath() )
	{
		DocName = DocFileName;
		table.open( __code4, (char*)GetDocPath());

		if ( Error() )
			return false;

		tag.initFirst( table );
		table.select( tag );

		if ( mode )
			NotifyViews( VN_VIEWTABLE_SAVED, (long)&table );

		else
		{
			if ( MatchTableType( TableType ))
				NotifyViews( VN_VIEWSETTYPE, (long)&TableType  );

			NotifyViews( VN_VIEWTABLE_OPENED, (long)&table );
		}

		return true;
	}

	else
	{
		if ( CreateTable( (int)__garq ) )
		{
			TableType = __garq;

			DocName   = GetTitle();
			SetTitle( DocName.c_str() );

			NotifyViews( VN_VIEWSETTYPE, (long)&TableType  );
			NotifyViews( VN_VIEWTABLE_OPENED, (long)&table );
		}
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                             Commit
//    ===============================
//
bool TTableDocument::Commit( bool force )
{
	DirtyFlag = false;						// Reset unsaved flag
	table.flush();                      // Flushes table data to disk
													// to prevent index corruption
	if ( DocFileName == GetDocPath() )	// 'SaveAs' needs to save to a
		return false;							// diferent file name and path

	::SetCursor( ::LoadCursor( 0, IDC_WAIT ));

	if ( !CopyFile( (char*)DocFileName.c_str(), (char*)GetDocPath() ) ) // Save current table
		return false;                                                    // to a new table file

	if ( !CopyMemo() )                  // Create MEMO file
		return false;                    // for the new table

	if ( !CopyIndex() )                 // Create INDEX file
		return false;                    // for the new table

	table.close();								// Close original table

	if ( DocFileName.contains( "WBO" ))	// If it was a 'Save' operation
		EraseTmpFile();                  // Erase '~WBO????.TMP' temp file

	return Open(1);							// Open new saved table
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                             Revert
//    ===============================
//
bool TTableDocument::Revert( bool clear )
{
	if ( clear )
		if ( IsDirty() )
			DirtyFlag = false;

	return true;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                         AppendData
//    ===============================
//
bool TTableDocument::AppendData( string& INdata )
{
	if( TableType == GARQBOR1 )
	{
		if ( FindCtrlDigit( INdata, 19 ) )
		{
			if ( INdata.contains( "ARQH" ) )
			{
				cod  = INdata.substr(  3, 1  );
				bols = INdata.substr(  4, 4  );
				date = INdata.substr(  8, 6  );

				string DD = date.substr( 0, 2 );
				string MM = date.substr( 2, 2 );
				string AA = date.substr( 4, 2 );

				date = "19" + AA + MM + DD;

				regs = INdata.substr( 14, 4  );
				bole = INdata.substr( 18, 1  );

				const char* v[] = { cod.c_str() , bols.c_str(), date.c_str(),
										  regs.c_str(), bole.c_str() };

				return AppendStart( v );
			}
		}
	}

	if( TableType == GARQBOR2 )
	{
		if ( FindCtrlDigit( INdata, 144 ) )
		{
			if ( INdata.contains( "ARQI" ) )
			{
				cod  = INdata.substr(  3, 1  );
				set  = INdata.substr(  4, 4  );
				vol  = INdata.substr(  5, 9  );
				qtd  = INdata.substr( 14, 9  );
				ibvm = INdata.substr( 23, 7  );
				osc  = INdata.substr( 30, 5  ); // osc.insert( 3, period );
				sin  = INdata.substr( 35, 1  );
				maxi = INdata.substr( 36, 7  );
				mini = INdata.substr( 47, 7  );
				ibvf = INdata.substr( 58, 7  );
				osc1 = INdata.substr( 65, 5  );
				sin1 = INdata.substr( 70, 1  );
				maxd = INdata.substr( 71, 7  );
				mind = INdata.substr( 82, 7  );

				const char* v[] = { cod.c_str() , set.c_str() , vol.c_str() ,
										  qtd.c_str() , ibvm.c_str(), osc.c_str() ,
										  sin.c_str() , maxi.c_str(), mini.c_str(),
										  ibvf.c_str(), osc1.c_str(), sin1.c_str(),
										  maxd.c_str(), mind.c_str() };

				return AppendStart( v );
			}
		}
	}

	if( TableType == GARQBOR3 )
	{
		if ( FindCtrlDigit( INdata, 70 ) )
		{
			if ( INdata.contains( "ARQB" ) )
			{
				cod  = INdata.substr(  3, 1  );
				prca = INdata.substr(  4, 3  );
				nom  = INdata.substr(  7, 30 );
				neg  = INdata.substr( 37, 11 );
				rea  = INdata.substr( 48, 5  );
				vol  = INdata.substr( 53, 17 ); // vol.insert( 15, period );

				const char* v[] = { cod.c_str(), prca.c_str(), nom.c_str(),
										  neg.c_str(), rea.c_str() , vol.c_str() };

				return AppendStart( v );
			}
		}
	}

	if( TableType == GARQBOR4 )
	{
		if ( FindCtrlDigit( INdata, 59 ) )
		{
			if ( INdata.contains( "ARQS" ) )
			{
				cod  = INdata.substr(  3, 1  );
				fec  = INdata.substr(  4, 7  );
				maxi = INdata.substr( 11, 7  );
				mini = INdata.substr( 18, 7  );
				med  = INdata.substr( 25, 7  );
				ult  = INdata.substr( 32, 7  );
				sin  = INdata.substr( 39, 1  );
				osc  = INdata.substr( 40, 5  ); // osc.insert( 3, period );
				imes = INdata.substr( 45, 7  );
				iano = INdata.substr( 52, 7  );

				const char* v[] = { cod.c_str() , fec.c_str(), maxi.c_str() ,
										  mini.c_str(), med.c_str(), ult.c_str()  ,
										  sin.c_str() , osc.c_str(), imes.c_str() ,
										  iano.c_str() };

				return AppendStart( v );
			}
		}
	}

	if( TableType == GARQBOR5 )
	{
		if ( FindCtrlDigit( INdata, 144 ) )
		{
			if ( INdata.contains( "ARQV" ) || INdata.contains( "ARQR" ) ||
				  INdata.contains( "ARQC" ) || INdata.contains( "ARQP" ) ||
				  INdata.contains( "ARQF" ) || INdata.contains( "ARQT" ) ||
				  INdata.contains( "ARQE" ) )
			{
				mer = INdata.substr(   3, 1  );
				cod = INdata.substr(   4, 4  );
				nom = INdata.substr(   8, 20 );

				tip = INdata.substr(  28, 2  );
				dir = INdata.substr(  30, 3  );
				ven = INdata.substr(  33, 3  );
				opc = INdata.substr(  36, 7  ); // opc.insert( 5, period );
				neg = INdata.substr(  43, 13 );

				abe = INdata.substr(  56, 7  ); // abe. insert( 5, period );
				fec = INdata.substr(  63, 7  ); // fec. insert( 5, period );
				maxi= INdata.substr(  70, 7  ); // maxi.insert( 5, period );
				mini= INdata.substr(  77, 7  ); // mini.insert( 5, period );
				med = INdata.substr(  84, 7  ); // med. insert( 5, period );
				osc = INdata.substr(  91, 5  ); // osc. insert( 3, period );

				sin = INdata.substr(  96, 1  );
				vol = INdata.substr(  97, 14 ); // vol.insert( 12, period );
				per = INdata.substr( 111, 6  ); // per.insert( 3, period );
				ind = INdata.substr( 117, 7  ); // ind.insert( 5, period );

				rea = INdata.substr( 124, 4  );
				com = INdata.substr( 128, 7  ); // com.insert( 5, period );
				vda = INdata.substr( 135, 7  ); // vda.insert( 5, period );
				uni = INdata.substr( 142, 1  );
				sit = INdata.substr( 143, 1  );

				const char* v[] = { mer.c_str(), cod.c_str(), nom.c_str() , tip.c_str() ,
										  dir.c_str(), ven.c_str(), opc.c_str() , neg.c_str() ,
										  abe.c_str(), fec.c_str(), maxi.c_str(), mini.c_str(),
										  med.c_str(), osc.c_str(), sin.c_str() , vol.c_str() ,
										  per.c_str(), ind.c_str(), rea.c_str() , com.c_str() ,
										  vda.c_str(), uni.c_str(), sit.c_str() };

				return AppendStart( v );
			}
		}
	}

	if( TableType == GARQBR )
	{
		if ( FindCtrlDigit( INdata, 128 ) )
		{
			mer = INdata.substr(   3, 1  );
			cod = INdata.substr(   4, 4  );
			nom = INdata.substr(   8, 20 );

			tip = INdata.substr(  28, 2  );
			dir = INdata.substr(  30, 3  );
			ven = INdata.substr(  33, 3  );
			opc = INdata.substr(  36, 7  ); // opc.insert( 5, period );
			neg = INdata.substr(  43, 13 );

			abe = INdata.substr(  56, 7  ); // abe. insert( 5, period );
			fec = INdata.substr(  63, 7  ); // fec. insert( 5, period );
			maxi= INdata.substr(  70, 7  ); // maxi.insert( 5, period );
			mini= INdata.substr(  77, 7  ); // mini.insert( 5, period );
			med = INdata.substr(  84, 7  ); // med. insert( 5, period );
			osc = INdata.substr(  91, 5  ); // osc. insert( 3, period );
			sin = INdata.substr(  96, 1  );

			vol = INdata.substr(  97, 14 ); // vol.insert( 12, period );
			per = INdata.substr( 111, 6  ); // per.insert( 3, period );
			ind = INdata.substr( 117, 7  ); // ind.insert( 5, period );

			rea = INdata.substr( 124, 4  );

			const char* v[] = { mer.c_str(), cod.c_str(), nom.c_str() , tip.c_str() ,
									  dir.c_str(), ven.c_str(), opc.c_str() , neg.c_str() ,
									  abe.c_str(), fec.c_str(), maxi.c_str(), mini.c_str(),
									  med.c_str(), osc.c_str(), sin.c_str() , vol.c_str() ,
									  per.c_str(), ind.c_str(), rea.c_str(), };

			return AppendStart( v );
		}
	}

	if( TableType == GARQBRI )
	{
		if ( FindCtrlDigit( INdata, 128 ) )
		{
			cod  = INdata.substr(  3, 1  );
			set  = INdata.substr(  4, 4  );
			vol  = INdata.substr(  5, 9  );
			qtd  = INdata.substr( 14, 9  );
			ibvm = INdata.substr( 23, 7  );
			osc  = INdata.substr( 30, 5  ); // osc.insert( 3, period );
			sin  = INdata.substr( 35, 1  );
			maxi = INdata.substr( 36, 7  );
			mini = INdata.substr( 47, 7  );
			ibvf = INdata.substr( 58, 7  );
			osc1 = INdata.substr( 65, 5  );
			sin1 = INdata.substr( 70, 1  );
			maxd = INdata.substr( 71, 7  );
			mind = INdata.substr( 82, 7  );

			const char* v[] = { cod.c_str() , set.c_str() , vol.c_str() ,
									  qtd.c_str() , ibvm.c_str(), osc.c_str() ,
									  sin.c_str() , maxi.c_str(), mini.c_str(),
									  ibvf.c_str(), osc1.c_str(), sin1.c_str(),
									  maxd.c_str(), mind.c_str() };

			return AppendStart( v );
		}
	}

	if( TableType == GARQBFR1 )
	{
		if ( FindCtrlDigit( INdata, 18 ) )
		{
			if ( INdata.contains( "ARQH" ) )
			{
				cod  = INdata.substr(  3, 1  );
				bols = INdata.substr(  4, 4  );
				date = INdata.substr(  8, 6  );

				string DD = date.substr( 0, 2 );
				string MM = date.substr( 2, 2 );
				string AA = date.substr( 4, 2 );

				date = "19" + AA + MM + DD;

				regs = INdata.substr( 14, 4  );

				const char* v[] = { cod.c_str() , bols.c_str(), date.c_str(),
										  regs.c_str() };

				return AppendStart( v );
			}
		}
	}

	if( TableType == GARQBFR2 )
	{
		if ( FindCtrlDigit( INdata, 128 ) )
		{
			if ( INdata.contains( "ARQI" ) )
			{
				cod  = INdata.substr(  3, 1  );
				set  = INdata.substr(  4, 1  );
				vol  = INdata.substr(  5, 9  );
				qtd  = INdata.substr( 14, 9  );
				fec  = INdata.substr( 23, 7  ); // fec .insert( 5, period );
				osc  = INdata.substr( 30, 5  ); // osc .insert( 3, period );
				sin  = INdata.substr( 35, 1  );
				maxi = INdata.substr( 36, 7  ); // maxi.insert( 5, period );
				mini = INdata.substr( 47, 7  ); // mini.insert( 5, period );
				ibvf = INdata.substr( 58, 7  ); // ibvf.insert( 5, period );
				osc1 = INdata.substr( 65, 5  ); // osc1.insert( 3, period );
				sin1 = INdata.substr( 70, 1  );
				maxd = INdata.substr( 71, 7  ); // maxd.insert( 5, period );
				mind = INdata.substr( 82, 7  ); // mind.insert( 5, period );

				const char* v[] = { cod.c_str() , set.c_str() , vol.c_str() ,
										  qtd.c_str() , fec.c_str() , osc.c_str() ,
										  sin.c_str() , maxi.c_str(), mini.c_str(),
										  ibvf.c_str(), osc1.c_str(), sin1.c_str(),
										  maxd.c_str(), mind.c_str() };

				return AppendStart( v );
			}
		}
	}

	if( TableType == GARQBFR3 )
	{
		if ( FindCtrlDigit( INdata, 128 ) )
		{
			if ( INdata.contains( "ARQV" ) || INdata.contains( "ARQR" ) ||
				  INdata.contains( "ARQC" ) || INdata.contains( "ARQP" ) ||
				  INdata.contains( "ARQF" ) || INdata.contains( "ARQT" ) )
			{
				mer = INdata.substr(   3, 1  );
				cod = INdata.substr(   4, 4  );
				nom = INdata.substr(   8, 20 );

				tip = INdata.substr(  28, 2  );
				dir = INdata.substr(  30, 3  );
				ven = INdata.substr(  33, 3  );
				opc = INdata.substr(  36, 7  ); // opc.insert( 5, period );
				neg = INdata.substr(  43, 13 );

				abe = INdata.substr(  56, 7  ); // abe. insert( 5, period );
				fec = INdata.substr(  63, 7  ); // fec. insert( 5, period );
				maxi= INdata.substr(  70, 7  ); // maxi.insert( 5, period );
				mini= INdata.substr(  77, 7  ); // mini.insert( 5, period );
				med = INdata.substr(  84, 7  ); // med. insert( 5, period );
				osc = INdata.substr(  91, 5  ); // osc. insert( 3, period );

				sin = INdata.substr(  96, 1  );
				vol = INdata.substr(  97, 14 ); // vol.insert( 12, period );
				per = INdata.substr( 111, 6  ); // per.insert( 3, period );
				ind = INdata.substr( 117, 7  ); // ind.insert( 5, period );

				rea = INdata.substr( 124, 4  );

				const char* v[] = { mer.c_str(), cod.c_str(), nom.c_str() , tip.c_str() ,
										  dir.c_str(), ven.c_str(), opc.c_str() , neg.c_str() ,
										  abe.c_str(), fec.c_str(), maxi.c_str(), mini.c_str(),
										  med.c_str(), osc.c_str(), sin.c_str() , vol.c_str() ,
										  per.c_str(), ind.c_str(), rea.c_str(), };

				return AppendStart( v );
			}
		}
	}

	if( TableType == GARQBS || TableType == GARQBAS2 )
	{
		if ( FindCtrlDigit( INdata, 136 ) )
		{
			nom = INdata.substr(   3, 12 );
			pap = INdata.substr(  15, 10 );
			idr = INdata.substr(  25, 1  );
			cod = INdata.substr(  26, 4  );
			num = INdata.substr(  30, 2  );
			mer = INdata.substr(  32, 3  );
			prz = INdata.substr(  35, 2  );
			cto = INdata.substr(  37, 2  );
			cdo = INdata.substr(  39, 4  );
			tip = INdata.substr(  43, 2  );
			esp = INdata.substr(  45, 4  );
			nbr = INdata.substr(  49, 3  );
			pri = INdata.substr(  52, 9  ); // pri.insert( 7, period );
			mai = INdata.substr(  61, 9  ); // mai.insert( 7, period );
			men = INdata.substr(  70, 9  ); // men.insert( 7, period );
			med = INdata.substr(  79, 9  ); // med.insert( 7, period );
			ult = INdata.substr(  88, 9  ); // ult.insert( 7, period );
			ten = INdata.substr(  97, 1  );
			osc = INdata.substr(  98, 5  ); // osc.insert( 3, period );
			com = INdata.substr( 103, 9  ); // com.insert( 7, period );
			vda = INdata.substr( 112, 9  ); // vda.insert( 7, period );
			ngc = INdata.substr( 121, 4  );
			neg = INdata.substr( 125, 11 );

			const char* v[] = { nom.c_str(), pap.c_str(), idr.c_str(), cod.c_str(),
									  num.c_str(), mer.c_str(), prz.c_str(), cto.c_str(),
									  cdo.c_str(), tip.c_str(), esp.c_str(), nbr.c_str(),
									  pri.c_str(), mai.c_str(), men.c_str(), med.c_str(),
									  ult.c_str(), ten.c_str(), osc.c_str(), com.c_str(),
									  vda.c_str(), ngc.c_str(), neg.c_str() };

			return AppendStart( v );
		}
	}

	if( TableType == GARQBSI || TableType == GARQBAS1 )
	{
		if ( FindCtrlDigit( INdata, 77 ) )
		{
			date = INdata.substr( 3, 8 );

			string DD = date.substr( 0, 2 );
			string MM = date.substr( 3, 2 );
			string AA = date.substr( 6, 2 );

			date = "19" + AA + MM + DD;

			abe  = INdata.substr( 11, 6  );
			mini = INdata.substr( 17, 6  );
			maxi = INdata.substr( 23, 6  );
			med  = INdata.substr( 29, 6  );
			fec  = INdata.substr( 35, 6  );
			ten  = INdata.substr( 41, 1  );
			evol = INdata.substr( 42, 4  ); // evol.insert( 3, period );
			ngc  = INdata.substr( 46, 5  );
			neg  = INdata.substr( 51, 13 );
			vol  = INdata.substr( 64, 13 ); // vol.insert( 11, period );

			const char* v[] = { date.c_str(), abe.c_str() , mini.c_str(),
									  maxi.c_str(), med.c_str() , fec.c_str() ,
									  ten.c_str() , evol.c_str(), ngc.c_str() ,
									  neg.c_str() , vol.c_str() };

			return AppendStart( v );
		}
	}

	if( TableType == GARQBRJDATA )
	{
		if ( FindCtrlDigit( INdata, 51 ) )
		{
			string date2, date3, date4, date5;

			set = INdata.substr(  0, 10 );
			tip = INdata.substr( 10, 1  );

			date = INdata.substr( 11, 8 );
			string DD = date.substr( 0, 2 );
			string MM = date.substr( 3, 2 );
			string AA = date.substr( 6, 2 );
			date = "19" + AA + MM + DD;

			date2 = INdata.substr( 19, 8 );
			DD = date2.substr( 0, 2 );
			MM = date2.substr( 3, 2 );
			AA = date2.substr( 6, 2 );
			date2 = "19" + AA + MM + DD;

			date3 = INdata.substr( 27, 8 );
			DD = date3.substr( 0, 2 );
			MM = date3.substr( 3, 2 );
			AA = date3.substr( 6, 2 );
			date3 = "19" + AA + MM + DD;

			date4 = INdata.substr( 35, 8 );
			DD = date4.substr( 0, 2 );
			MM = date4.substr( 3, 2 );
			AA = date4.substr( 6, 2 );
			date4 = "19" + AA + MM + DD;

			date5 = INdata.substr( 43, 8 );
			DD = date5.substr( 0, 2 );
			MM = date5.substr( 3, 2 );
			AA = date5.substr( 6, 2 );
			date5 = "19" + AA + MM + DD;

			const char* v[] = { set.c_str()  , tip.c_str()  , date.c_str() ,
									  date2.c_str(), date3.c_str(), date4.c_str(),
									  date5.c_str() };

			return AppendStart( v );
		}
	}

	if( TableType == GARQBSPDATA )
	{
		if ( FindCtrlDigit( INdata, 18 ) )
		{
			set  = INdata.substr( 0, 10 );
			date = INdata.substr( 10, 8 );

			string DD = date.substr( 0, 2 );
			string MM = date.substr( 3, 2 );
			string AA = date.substr( 6, 2 );

			date = "19" + AA + MM + DD;

			const char* v[] = { set.c_str(), date.c_str() };
			return AppendStart( v );
		}
	}

	if( TableType == GARQBIG )
	{
		if ( FindCtrlDigit( INdata, 42 ) )
		{
			ExtractStockCode( INdata );

			ult = INdata.substr( 15, 7 ); // ult.insert( 5, period );
			med = INdata.substr( 22, 7 ); // med.insert( 5, period );
			fec = INdata.substr( 29, 7 ); // fec.insert( 5, period );

			hor = INdata.substr( 36, 6 );
			hor.insert( 2, colon );
			hor.insert( 5, colon );

			const char* v[] = { date.c_str(), hor.c_str(), cod.c_str(),
									  tip.c_str (), dir.c_str(), ven.c_str(),
									  ult.c_str (), med.c_str(), fec.c_str() };

			return AppendStart( v );
		}
	}

	if( TableType == GARQNEG )
	{
		if ( FindCtrlDigit( INdata, 41, 57 ) )
		{
			cod  = INdata.substr(  3, 4 );
			tip  = INdata.substr(  7, 2 );
			dir  = INdata.substr(  9, 3 );
			ven  = INdata.substr( 12, 3 );

			neg  = INdata.substr( 15, 7 );
			opc  = INdata.substr( 22, 7 ); // opc.insert( 5, period );

			date = INdata.substr( 29, 6 );

			string DD = date.substr( 0, 2 );
			string MM = date.substr( 2, 2 );
			string AA = date.substr( 4, 2 );

			date = "19" + AA + MM + DD;
			hor  = INdata.substr( 35, 6 );

			hor.insert( 2, colon );
			hor.insert( 5, colon );

			if ( INdata.length() == 57 )
			{
				ngc  = INdata.substr( 41, 9 );
				cra  = INdata.substr( 50, 3 );
				tpo  = INdata.substr( 53, 1 );
				crb  = INdata.substr( 54, 3 );
			}
			else
			{
				ngc  = "000000000";
				cra  = "   ";
				tpo  = " ";
				crb  = "   ";
			}

			const char* v[] = { cod.c_str(), tip.c_str(), dir.c_str(),  ven.c_str(),
									  neg.c_str(), opc.c_str(), date.c_str(), hor.c_str(),
									  ngc.c_str(), cra.c_str(), tpo.c_str() , crb.c_str() };

			return AppendStart( v );
		}
	}

	if( TableType == GARQHIS )
	{
		if ( FindCtrlDigit( INdata, 79 ) )
		{
			ExtractStockCode( INdata );

			osc  = INdata.substr( 15, 5  ); // osc.insert ( 3, period );
			sin  = INdata.substr( 20, 1  );

			mini = INdata.substr( 21, 7  ); // mini.insert( 5, period );
			maxi = INdata.substr( 28, 7  ); // maxi.insert( 5, period );
			med  = INdata.substr( 35, 7  ); // med .insert( 5, period );
			abe  = INdata.substr( 42, 7  ); // abe .insert( 5, period );
			fec  = INdata.substr( 49, 7  ); // fec .insert( 5, period );

			neg  = INdata.substr( 56, 13 );
			rea  = INdata.substr( 69, 4  );
			date = INdata.substr( 73, 6  );

			string DD = date.substr( 0, 2 );
			string MM = date.substr( 2, 2 );
			string AA = date.substr( 4, 2 );

			date = "19" + AA + MM + DD;

			const char* v[] = { date.c_str(), cod.c_str(), tip.c_str(), dir.c_str (),
									  ven.c_str (), osc.c_str(), sin.c_str(), mini.c_str(),
									  maxi.c_str(), med.c_str(), abe.c_str(), fec.c_str (),
									  neg.c_str (), rea.c_str() };

			return AppendStart( v );
		}
	}

	if( TableType == GARQIND )
	{
		if ( FindCtrlDigit( INdata, 27 ) )
		{
			set  = INdata.substr( 3, 2 );
			date = INdata.substr( 5, 6 );

			string AA = date.substr( 0, 2 );
			string MM = date.substr( 2, 2 );
			string DD = date.substr( 4, 2 );

			date = "19" + AA + MM + DD;

			ibvm = INdata.substr( 11, 8 );
			ibvf = INdata.substr( 19, 8 );

			const char* v[] = { set.c_str(), date.c_str(), ibvm.c_str(), ibvf.c_str() };
			return AppendStart( v );
		}
	}

	return false;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                        AppendStart
//    ===============================
//
bool TTableDocument::AppendStart( const char* v[] )
{
	Field4 field;

	for ( int n = 1; n <= table.numFields(); n++ )
	{
		field.init( table, n );
		if ( !IsValidField( field, (char*)v[ n-1 ] ) )
			return false;
	}

	table.appendStart();

	for ( int n = 1; n <= table.numFields(); n++ )
	{
		field.init( table, n );
		field.assign( (char*)v[ n-1 ] );
	}

	if ( !IsDirty() )
		if ( DocName.contains( "Document" ) )
			DirtyFlag = true;

	table.append();
	return true;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                       IsValidField
//    ===============================
//
bool TTableDocument::IsValidField( Field4& field, char* str )
{
	bool ret = true;

	if ( field.type() == 'N' )
	{
		while ( *str ) {
			if ( !isdigit( *str ) && *str != '.' ) {
				ret = false;
				break;
			}
			str++;
		}
	}

	if ( field.type() == 'C' )
	{
		string s = " ~^'`,;_=+-/\:.";

		while ( *str ) {
			if ( *str == '\x1C' )
				*str = ' ';

			if ( !isalnum( *str ) && !s.contains( *str ) ) {
				ret = false;
				break;
			}
			str++;
		}
	}

	if ( field.type() == 'D' )
	{
		string v = str;

		while ( *str ) {
			if ( !isdigit( *str ) && *str != '.' ) {
				ret = false;
				break;
			}
			str++;
		}

		if ( ret )
		{
			unsigned Day, Month, Year;

			Day   = atoi( v.substr( 6, 2 ).c_str() );
			Month = atoi( v.substr( 4, 2 ).c_str() );
			Year  = atoi( v.substr( 2, 2 ).c_str() );

			TDate d( Day, Month, Year );

			if ( !d.IsValid() )
				ret = false;
		}
	}
	return ret;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                         UpdateView
//    ===============================
//
void TTableDocument::UpdateView()
{
	NotifyViews( VN_VIEWUPDATE, 0L );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                          CopyIndex
//    ===============================
//
bool TTableDocument::CopyIndex()
{
	Tag4info TagInfo( table );	// Get index information
										// from original table
	if ( TagInfo.numTags() )	// If there was a
   {									// production index
      string IN  = DocFileName;
      string OUT = GetDocPath();
		size_t pos = IN.find( ".DBF" );

		if ( pos == NPOS )
      	pos = IN.find( ".TMP" );

      IN. replace( pos, 4, ".CDX" );
		OUT.replace( OUT.find( ".DBF" ), 4, ".CDX" );

      return CopyFile( (char*)IN.c_str(), (char*)OUT.c_str() );
	}
	return true;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                           CopyFile
//    ===============================
//
bool TTableDocument::CopyFile( char* INFile, char* OUTFile )
{
	OUT.create( __code4, OUTFile );			// Create file for writing

   if ( Error( true ))
   	return false;

	IN.open( __code4, INFile );				// Open file for reading

	if ( Error( true ))
		return false;

	long Length    = IN.len();
	long lpos      = 0L;
	long BytesRead = 0L;
														// 31Kb buffer for reading when
	Str4flex s4( __code4 );                // dealing with bigger files
	s4.setLen( Length >= 31744L ? (unsigned)31744L : (unsigned)Length );

	if ( Error( true ))
		return false;

	do {
		lpos = IN.read( BytesRead, s4 );
		OUT.write( BytesRead, s4 );

		BytesRead += lpos;

	} while ( BytesRead < Length );

   IN.close();									// Close input file
   s4.free();

	OUT.close();								// Close output file

   if ( Error( true ))
   	return false;

	return true;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                           CopyMemo
//    ===============================
//
bool TTableDocument::CopyMemo()
{
	Field4 field;
	bool HasMemoField = false;

	for ( int n = 1; n <= table.numFields(); n++ )
	{
		field.init( table, n );

		if ( field.type() == 'M' )
		{
			HasMemoField = true;
			break;
		}
	}

	if ( HasMemoField )
	{
		string IN  = DocFileName;
		string OUT = GetDocPath();
		size_t pos = IN.find( ".DBF" );

		if ( pos == NPOS )
			pos = IN.find( ".TMP" );

		IN. replace( pos, 4, ".FPT" );
		OUT.replace( OUT.find( ".DBF" ), 4, ".FPT" );

		return CopyFile( (char*)IN.c_str(), (char*)OUT.c_str() );
	}
	return true;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                        CreateTable
//    ===============================
//
bool TTableDocument::CreateTable( int type )
{
	bool rc = true;

	char buff[ MAXPATH ] = "";
	GetTempFileName( 0, "WBO", 0, buff );	// Creates a temporary file

	remove( buff );                        // Deletes the temporary file
	DocFileName = buff;                    // Uses it's name for the new table

	switch ( type )
	{
		case 1  :
			table.create( __code4, buff, GarqBOR1Fields, GarqBOR1Tags );
			break;

		case 2  :
			table.create( __code4, buff, GarqBOR2Fields, GarqBOR2Tags );
			break;

		case 3  :
			table.create( __code4, buff, GarqBOR3Fields, GarqBOR3Tags );
			break;

		case 4  :
			table.create( __code4, buff, GarqBOR4Fields );
			break;

		case 5  :
			table.create( __code4, buff, GarqBOR5Fields, GarqBORTags );
			break;

		case 6  :
			table.create( __code4, buff, GarqBRxFields, GarqBRxTags );
			break;

		case 7  :
			table.create( __code4, buff, GarqBRIFields, GarqBRITags );
			break;

		case 8  :
			table.create( __code4, buff, GarqBFR1Fields, GarqBFR1Tags );
			break;

		case 9  :
			table.create( __code4, buff, GarqBFR2Fields, GarqBFR2Tags );
			break;

		case 10 :
			table.create( __code4, buff, GarqBFR3Fields, GarqBFR3Tags );
			break;

		case 11 :
			table.create( __code4, buff, GarqBSxFields, GarqBSxTags );
			break;

		case 12 :
			table.create( __code4, buff, GarqBSIFields, GarqBSITags );
			break;

		case 13 :
			table.create( __code4, buff, GarqBAS1Fields, GarqBAS1Tags );
			break;

		case 14 :
			table.create( __code4, buff, GarqBAS2Fields, GarqBAS2Tags );
			break;

		case 15 :
			table.create( __code4, buff, GarqBRJDATAFields );
			break;

		case 16 :
			table.create( __code4, buff, GarqBSPDATAFields );
			break;

		case 17 :
			table.create( __code4, buff, GarqBIGFields, GarqBIGTags );
			break;

		case 18 :
			table.create( __code4, buff, GarqNEGFields, GarqNEGTags );
			break;

		case 19 :
			table.create( __code4, buff, GarqHISFields, GarqHISTags );
			break;

		case 20 :
			table.create( __code4, buff, GarqINDFields, GarqINDTags );
			break;

		default :
			rc = false;
			::MessageBox( 0, "Opção não implementada.", "WinBolsa® - Aviso",
							  MB_OK | MB_ICONINFORMATION );
			break;
	}

	if ( Error() )
		rc = false;

	return rc;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                         CloseTable
//    ===============================
//
void TTableDocument::CloseTable()
{
	if ( table.isValid() )
	{
		table.close();

		if ( DocName.contains( "Document" ))
			EraseTmpFile();
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                       EraseTmpFile
//    ===============================
//
void TTableDocument::EraseTmpFile()
{
	string index = DocFileName;
	size_t pos   = index.find( ".TMP" );

	if ( pos == NPOS )
		pos = index.find( ".DBF" );

	index.replace( pos, 4, ".CDX" );

	remove( DocFileName.c_str() );
	remove( index.c_str() );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                              Error
//    ===============================
//
bool TTableDocument::Error( bool CommitError )
{
	if ( __code4.errorCode )
	{
		if ( CommitError )
		{
			SetDocPath( 0 );
			SetTitle( DocName.c_str() );

			::MessageBox( 0, "Erro. Gravação não pode ser efetuada", "WinBolsa® - Aviso",
							  MB_OK | MB_ICONQUESTION );
		}
		else
			::MessageBox( 0, "Erro. Documento não pode ser aberto", "WinBolsa® - Aviso",
							  MB_OK | MB_ICONQUESTION );

		__code4.errorCode = 0;
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                   ExtractStockCode
//    ===============================
//
void TTableDocument::ExtractStockCode( string& INdata )
{
	cod = INdata.substr(  3, 4 );
	tip = INdata.substr(  7, 2 );
	dir = INdata.substr(  9, 3 );
	ven = INdata.substr( 12, 3 );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                      FindCtrlDigit
//    ===============================
//
bool TTableDocument::FindCtrlDigit( string& INdata, size_t cdp, size_t cdp_2 )
{
	// Adjust string contents before verifying
	INdata = INdata.substr( INdata.find( "/.ARQ" ) + 2 );

	// Check for control digit position
	size_t p = INdata.find( "!" );

	if ( p == cdp )
		return true;

	if ( cdp_2 )
		if ( p == cdp_2 )
			return true;

	return false;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableDocument
//                     MatchTableType
//    ===============================
//
bool TTableDocument::MatchTableType( GARQ_TYPE& TableType )
{
	Field4info fld4info( table );
	FIELD4INFO *fld4tmp = fld4info.fields();

	for ( int i = 0; i < MAX_GARQ_TYPES; i++ )
   {
		if ( fld4info.numFields() == GarqNumFldsInfo[ i ] )
      {
         DBFfieldInfo i1( GarqField4Info[ i ] );
         DBFfieldInfo i2( fld4tmp );

			if ( i1 == i2 )
			{
				TableType = (GARQ_TYPE)i;
				return true;
			}
      }
   }

	return false;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableView
//                     RESPONSE_TABLE
//    ===============================
//
DEFINE_RESPONSE_TABLE3( TTableView, TView, TLayoutWindow, TVbxEventHandler )
	EV_VN_ISWINDOW,
	EV_OWLNOTIFY( VN_VIEWTABLE_OPENED, VnTableOpened  ),
	EV_OWLNOTIFY( VN_VIEWTABLE_SAVED,  VnTableSaved   ),
	EV_OWLNOTIFY( VN_VIEWSETTYPE,      VnSetViewType  ),
	EV_OWLNOTIFY( VN_VIEWUPDATE,       VnViewUpdate   ),
END_RESPONSE_TABLE;

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableView
//                        CONSTRUCTOR
//    ===============================
//
TTableView::TTableView( TTableDocument& doc, TWindow* parent )
								: TView( doc ), TLayoutWindow( parent )
{
	Init( parent, 0, 0 );

	// Preset the 'ViewType' since the 'VnSetViewType'
	// will not be fired when opening a standard DBF table
	ViewType = NOGARQ;

	// Pointers must be NULL before calling 'Open' function
	// to prevent a GPF when the 'VnIsWindow' event is fired
	GridVBX  = 0;
	Label    = 0;
	table    = 0;

	// 'VnTableOpened' and 'VnSetViewType' events are fired by
	// the 'Open' function updating the view type and DBF table
	if ( !Doc->Open(0) )
		NotOK();

	if ( IsOK() )
	{
		GridVBX = new TBrowseCtl( (Data4*)table, this, IDC_GRIDVBX );
		Label   = new TLabel( this, GarqLabel[ ViewType ], GetSysColor( COLOR_BTNFACE ), 0, 0 );

		lm1.X.Set     ( lmLeft   , lmAbsolute , lmParent  , lmLeft   );
		lm1.Width.Set ( lmWidth  , lmSameAs   , lmParent  , lmWidth  );
		lm1.Y.Set     ( lmTop    , lmSameAs   , lmParent  , lmTop    );
		lm1.Height.Set( lmHeight , lmAbove    , Label     , lmTop    );

		lm2.X.Set     ( lmLeft   , lmAbsolute , lmParent  , lmLeft   );
		lm2.Width.Set ( lmWidth  , lmSameAs   , lmParent  , lmWidth  );
		lm2.Y.Set     ( lmBottom , lmSameAs   , lmParent  , lmBottom );
		lm2.Height.Set( lmHeight , lmAbsolute , lmParent  , lmHeight , 8 );

		SetChildLayoutMetrics( *GridVBX, lm1 );
		SetChildLayoutMetrics( *Label  , lm2 );
	}
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableView
//                           CanClose
//    ===============================
//
bool TTableView::CanClose()
{
	return Doc->CanClose() && TLayoutWindow::CanClose();
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableView
//                        SetDocTitle
//    ===============================
//
bool TTableView::SetDocTitle( LPCSTR docname, int index )
{
	if ( Doc->GetDocPath() )
		return TWindow::SetDocTitle( Doc->GetDocPath(), index );
	else
		return TWindow::SetDocTitle( docname, index );
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableView
//                         VnIsWindow
//    ===============================
//
bool TTableView::VnIsWindow( HWND hWnd )
{
	bool r = ( *this == hWnd );

	if ( !r )
		if ( GridVBX )
			r = ( *GridVBX == hWnd );

	if ( !r )
		if ( Label )
			r = ( *Label == hWnd );

	return r;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableView
//                      VnTableOpened
//    ===============================
//
bool TTableView::VnTableOpened( long v )
{
	table = (Data4*)v;
	return true;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableView
//                       VnTableSaved
//    ===============================
//
bool TTableView::VnTableSaved( long v )
{
	GridVBX->Destroy();
	delete GridVBX;

	table   = (Data4*)v;
	GridVBX = new TBrowseCtl( table, this, IDC_GRIDVBX );

	GridVBX->Create();
	SetChildLayoutMetrics( *GridVBX, lm1 );

	Layout();
	return true;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableView
//                      VnSetViewType
//    ===============================
//
bool TTableView::VnSetViewType( long type )
{
	ViewType = *((GARQ_TYPE*)type);
	return true;
}

//----------------------------------------------------------------------------//

/////////////////////////////////////
//    TTableView
//                       VnViewUpdate
//    ===============================
//
bool TTableView::VnViewUpdate( long dummy )
{
	GridVBX->UpdateDisplay();
	return true;
}

