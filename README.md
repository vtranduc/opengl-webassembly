## Engine set up

Go to engine folder\
`cd engine/`\
First, convert glsl into C++ code by creating headerSource.h\
`sh toGLchar.sh`\
Execute build.sh inside to build the engine\
`sh build.sh`\
Engine is built inside public folder. You want to disable autorefresh for files inside public folder.\
To do this, after installation, locate\
`node_modules\react-scripts\config\webpackDevServer.config.js`\
Then, include public folder. `ignored` specifications should look like\
`ignored: [ignoredFiles(paths.appSrc), paths.appPublic]`

## Adding glsl

All glsl files should have .glsl extensions.

- Vertex shader should be put inside `engine/glsl/vertex`
- Fragment shader should be put inside `engine/glsl/fragment`
  Now, modify content of this 1 file
  `engine/headers/shader.h`
- Add enum for shader with unique integer assigned. These integers help to create switch case inside shaderSource.h . The code should work regardless of value assigned.
- Update the count of nVertex/nFragment
- Update the array vertexList/fragmentList to they contain all enums
- Update getFileName(Vertex shader)/getFileName(Fragment shader) functions so the switch case contains newly added enum and corresponding glsl file name.

# Getting Started with Create React App

This project was bootstrapped with [Create React App](https://github.com/facebook/create-react-app).

## Available Scripts

In the project directory, you can run:

### `npm start`

Runs the app in the development mode.\
Open [http://localhost:3000](http://localhost:3000) to view it in the browser.

The page will reload if you make edits.\
You will also see any lint errors in the console.

### `npm test`

Launches the test runner in the interactive watch mode.\
See the section about [running tests](https://facebook.github.io/create-react-app/docs/running-tests) for more information.

### `npm run build`

Builds the app for production to the `build` folder.\
It correctly bundles React in production mode and optimizes the build for the best performance.

The build is minified and the filenames include the hashes.\
Your app is ready to be deployed!

See the section about [deployment](https://facebook.github.io/create-react-app/docs/deployment) for more information.

### `npm run eject`

**Note: this is a one-way operation. Once you `eject`, you can’t go back!**

If you aren’t satisfied with the build tool and configuration choices, you can `eject` at any time. This command will remove the single build dependency from your project.

Instead, it will copy all the configuration files and the transitive dependencies (webpack, Babel, ESLint, etc) right into your project so you have full control over them. All of the commands except `eject` will still work, but they will point to the copied scripts so you can tweak them. At this point you’re on your own.

You don’t have to ever use `eject`. The curated feature set is suitable for small and middle deployments, and you shouldn’t feel obligated to use this feature. However we understand that this tool wouldn’t be useful if you couldn’t customize it when you are ready for it.

## Learn More

You can learn more in the [Create React App documentation](https://facebook.github.io/create-react-app/docs/getting-started).

To learn React, check out the [React documentation](https://reactjs.org/).
