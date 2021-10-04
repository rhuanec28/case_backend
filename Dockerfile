# montando a imagem principal a partir do php7
FROM php:7.4-apache
# instalando dependencias gerais, nodejs e lib do postgres
RUN apt-get update && apt-get install -y nodejs npm && apt-get install -y libpq-dev

WORKDIR /usr/app

# copiando arquivos de config do nodejs
COPY package*.json ./

# instalando a lib do postgres para php, possibilitando a comunicação do backend com o banco de dados
RUN docker-php-ext-configure pgsql -with-pgsql=/usr/local/pgsql \
    && docker-php-ext-install pgsql pdo_pgsql

# instalando o framework nextjs e dependencias do react
RUN npm install next react react-dom

# iniciando o serviço do nextjs, fazendo o deploy do framework na porta 3000
# CMD ["npm", "run", "dev"]