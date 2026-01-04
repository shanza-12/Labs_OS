# Use Node.js image
FROM node:18

# Set working directory
WORKDIR /app

# Copy package.json and install dependencies
COPY package.json .
RUN npm install

# Copy backend source code
COPY . .

# Expose port
EXPOSE 3000

# Start server
CMD ["node", "server.js"]
