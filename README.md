# IoTupã

<h2>Resumo</h2>
<p>A diferença meteorológica entre centros urbanos e regiões periféricas é algo recorrente. Em particular, esta situação acontece, por exemplo, ao comparar o campus samambaia e outras regiões da cidade, quando uma pode estar ensolarada e a outra com chuva.  O objetivo principal deste trabalho foi a elaboração de uma estação meteorológica constituída de materiais de baixo custo que fornecesse as aferições de seus sensores em tempo real em uma plataforma web de acesso livre, de maneira que pudesse informar aos usuários como está o tempo no campus Samambaia da Universidade Federal de Goiás no momento do acesso. O intuito deste trabalho foi criar uma solução no contexto de cidades inteligentes e internet das coisas. O projeto foi desenvolvido com base na plataforma Arduino acoplando a ela sensores que medem variáveis meteorológicas, com termômetro, higrômetro e sensor de chuva.  A estação possui conexão à internet e a um banco de dados onde os registros são armazenados. Como resultado, tem-se a elaboração e entrega de um protótipo componente de software inovador baseado em aplicação IoT para percepção em tempo real de condições meteorológicas no ambiente onde está instalado.</p>

<h2>1. Introdução</h2>
<p>O campus universitário Samambaia da Universidade Federal de Goiás (UFG) localiza-se, em linha reta, a uma distância de aproximadamente nove quilômetros e meio do centro da cidade de Goiânia e a cerca de 30 quilômetros da cidade de Aparecida de Goiânia e Trindade. As distâncias entre o campus e essas regiões urbanas, somadas à diferente densidade demográfica e área de vegetação resultam em condições meteorológicas frequentemente divergentes entre a universidade e seu entorno e as demais localidades citadas anteriormente.
	O acompanhamento das condições meteorológicas de um determinado local em tempo real é uma informação que pode ser de interesse das pessoas, seja para a tomada de decisões a situações mais complexas como a execução de uma atividade de campo ou para situações mais simples como escolher a vestimenta adequada para deslocar-se para a universidade, que apesar de o campus dispor de uma estação meteorológica na Escola de Agronomia, os dados não são entregues em tempo real, não podendo ser utilizados pela comunidade universitária, o que justifica a pesquisa proposta.
	Neste sentido, a tecnologia denominada internet das coisas (internet of things, IoT) é uma possível solução para disponibilizar informações das variáveis climáticas em tempo real em uma plataforma web de livre acesso. Com a utilização de um  software embarcado em uma placa microcontroladora que tenha acesso à internet é possível acoplar sensores de umidade, temperatura e chuva que permitam a  coleta de dados meteorológicos e a sua disponibilização em tempo real.
	Diante disso, a contribuição deste projeto é desenvolver uma solução tecnológica com base em sensores e internet das coisas para disponibilizar um serviço gratuito e em tempo real das condições meteorológicas na UFG /Samambaia e disponibilizá-los para a conveniência da comunidade universitária.
	Este trabalho está organizado da seguinte forma: a Seção 2 trata do referencial teórico do trabalho; a Seção 3 trata da metodologia de pesquisa utilizada ; a Seção 4 trata do desenvolvimento do projeto ; a Seção 5 trata da avaliação do projeto; a Seção 6 trata da discussão ; a Seção 7 trata das considerações finais.
</p>

<h2>2. Referencial Teórico</h2>
<h2>2.1 Estações Meteorológicas</h2>
<p>O termo meteorologia vem da palavra grega meteoros, que significa "alto no ar" [1]. Meteorologia de modo genérico é a ciência que estuda a atmosfera terrestre se baseando em fenômenos naturais para a previsão do tempo e para estabelecer características climatológicas de uma região. É uma ciência ambiental indispensável para várias áreas da sociedade desde a agricultura até os transportes aéreos. Uma estação meteorológica utiliza de diversos instrumentos para realizar a medição das variáveis climáticas para que assim possa através desses dados obter informações das condições atmosféricas. 
</p>

<h2>2.2 Internet Of Things (IOT)</h2>
<p>A Internet das Coisas (IoT) é um paradigma de comunicação recente no qual os objetos da vida cotidiana serão equipados com microcontroladores,  transceptores para comunicação digital e pilhas de protocolo adequadas que os tornarão capazes de comunicarem entre si e com os usuários, tornando-se parte integrante da Internet [2].
	Placas wemos D1 são exemplos de dispositivos IoT capaz de se comunicar com a rede encaminhando pacotes de dados de forma periódica.
</p> 

<h2>2.3 Big Data</h2>
<p>Big data é um termo para conjuntos de dados massivos que possuem uma estrutura grande, mais variada e complexa com as dificuldades de armazenamento, análise e visualização para processos ou resultados futuros [3].
	O crescimento dos dados produzidos via IoT tem desempenhado um papel importante no cenário de big data. Big data pode ser categorizado de acordo com três aspectos: (a) volume,(b) variedade e (c) velocidade [4]. A leitura de sensores em um ambiente fornece um imenso volume de dados variados em uma determinada velocidade, dados esses que podem ser analisados para que se possam extrair informações interessantes e sirvam como ferramenta de estudo e até mesmo como um importante meio para a tomada de decisões.
</p> 

<h2>2.4 Plataforma Arduino</h2>
<p>Arduino é uma plataforma eletrônica de código aberto baseada em hardware e software fáceis de usar. As placas Arduino são capazes de ler entradas - luz em um sensor, um dedo em um botão ou uma mensagem do Twitter - e transformá-la em uma saída - ativando um motor, ligando um LED, publicando algo online. Um conjunto de instruções pode ser inserido no microcontrolador na placa para guiar as ações desempenhadas por ela. Para fazer isso, utiliza-se a linguagem de programação Arduino (baseada em Wiring) e o Software Arduino (IDE), baseado em Processing. [5]
	As placas Arduino ou baseadas na plataforma Arduino, como é o caso da Wemos D1 que foi utilizada neste projeto, são o principal componente do circuito sendo responsável por armazenar o algoritmo, processar dados, acionar eventuais atuadores, receber medições de sensores, estabelecer a conexão com a internet, estabelecer conexão com o banco de dados e acoplar demais instrumentos que possam ser úteis à execução do projeto como o caso de shields que são capazes de aumentar as funcionalidades da placa. 
</p>



