function varargout = ledopengui(varargin)
%LEDOPENGUI MATLAB code file for ledopengui.fig
%      LEDOPENGUI, by itself, creates a new LEDOPENGUI or raises the existing
%      singleton*.
%
%      H = LEDOPENGUI returns the handle to a new LEDOPENGUI or the handle to
%      the existing singleton*.
%
%      LEDOPENGUI('Property','Value',...) creates a new LEDOPENGUI using the
%      given property value pairs. Unrecognized properties are passed via
%      varargin to ledopengui_OpeningFcn.  This calling syntax produces a
%      warning when there is an existing singleton*.
%
%      LEDOPENGUI('CALLBACK') and LEDOPENGUI('CALLBACK',hObject,...) call the
%      local function named CALLBACK in LEDOPENGUI.M with the given input
%      arguments.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help ledopengui

% Last Modified by GUIDE v2.5 23-Jan-2022 01:38:55

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @ledopengui_OpeningFcn, ...
                   'gui_OutputFcn',  @ledopengui_OutputFcn, ...
                   'gui_LayoutFcn',  [], ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
   gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before ledopengui is made visible.
function ledopengui_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   unrecognized PropertyName/PropertyValue pairs from the
%            command line (see VARARGIN)

% Choose default command line output for ledopengui
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes ledopengui wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = ledopengui_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in ledon.
function ledon_Callback(hObject, eventdata, handles)
% hObject    handle to ledon (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in led_close.
function led_close_Callback(hObject, eventdata, handles)
% hObject    handle to led_close (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in endconnection.
function endconnection_Callback(hObject, eventdata, handles)
% hObject    handle to endconnection (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
