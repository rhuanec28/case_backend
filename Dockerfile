FROM php:7.4-apache
RUN apt-get update && apt-get install -y nodejs npm && apt-get install -y libpq-dev

WORKDIR /usr/app

COPY package*.json ./

RUN docker-php-ext-configure pgsql -with-pgsql=/usr/local/pgsql \
    && docker-php-ext-install pgsql pdo_pgsql
RUN npm install next react react-dom

# CMD ["npm", "run", "dev"]